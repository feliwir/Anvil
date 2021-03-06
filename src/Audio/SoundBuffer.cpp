/*
************************************
* Copyright (C) 2016 ByteForge
* SoundBuffer.cpp
************************************
*/

#include "SoundBuffer.hpp"
#include "../Exception.hpp"
#include <iostream>
#include <fstream>
#include <stdint.h>
using namespace anvil;

//WAV FILE FORMAT
/**
 * Struct that holds the RIFF data of the Wave file.
 * The RIFF data is the meta data information that holds,
 * the ID, size and format of the wave file
 */
struct RIFF_Header 
{
	char chunkID[4];
	uint32_t chunkSize;//size not including chunkSize or chunkID
	char format[4];
};

/**
 * Struct to hold fmt subchunk data for WAVE files.
 */
struct WAVE_Format 
{
	char subChunkID[4];
	uint32_t subChunkSize;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
};

/**
 * Struct to hold the data of the wave file
 */
struct WAVE_Data {
	char subChunkID[4]; //should contain the word data
	uint32_t subChunk2Size; //Stores the size of the data block
};
//END WAV FILE FORMAT


SoundBuffer::SoundBuffer() : m_buffer(0)
{
    alGenBuffers(1,&m_buffer);
}

SoundBuffer::~SoundBuffer()
{
    if(m_buffer)
        alDeleteBuffers(1,&m_buffer);
}

bool SoundBuffer::Load(const std::string & path)
{
	std::ifstream fin;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	char* data;

	fin.open(path, std::ios::binary);
	if (fin.fail())
	{
		return false;
	}		

	fin.read(reinterpret_cast<char*>(&riff_header), sizeof(RIFF_Header));
	if ((riff_header.chunkID[0] != 'R' ||
		 riff_header.chunkID[1] != 'I' ||
		 riff_header.chunkID[2] != 'F' ||
		 riff_header.chunkID[3] != 'F') ||
		 (riff_header.format[0] != 'W' ||
	      riff_header.format[1] != 'A' ||
		  riff_header.format[2] != 'V' ||
		  riff_header.format[3] != 'E'))
		throw AnvilException("Invalid .wav file header: " + path, __FILE__, __LINE__);

	fin.read(reinterpret_cast<char*>(&wave_format), sizeof(WAVE_Format));
	if (wave_format.subChunkID[0] != 'f' ||
		wave_format.subChunkID[1] != 'm' ||
		wave_format.subChunkID[2] != 't' ||
		wave_format.subChunkID[3] != ' ')
		throw AnvilException("Invalid .wav file format chunk: " + path, __FILE__, __LINE__);

	if (wave_format.subChunkSize > 16)
		fin.seekg(sizeof(short), std::ios::cur);

	//Read in the the last byte of data before the sound file
	fin.read(reinterpret_cast<char*>(&wave_data), sizeof(WAVE_Data));
	//check for data tag in memory
	if (wave_data.subChunkID[0] != 'd' ||
		wave_data.subChunkID[1] != 'a' ||
		wave_data.subChunkID[2] != 't' ||
		wave_data.subChunkID[3] != 'a')
		throw AnvilException("Invalid .wav file data chunk: " + path, __FILE__, __LINE__);

	//Allocate memory for data
	data = new char[wave_data.subChunk2Size];

	// Read in the sound data into the soundData variable
	if (!fin.read(data, wave_data.subChunk2Size))
		throw AnvilException("Error loading wave data into chunk: " + path, __FILE__, __LINE__);

	//Now we set the variables that we passed in with the
	//data from the structs
	m_size = wave_data.subChunk2Size;
	m_frequency = wave_format.sampleRate;
	//The format is worked out by looking at the number of
	//channels and the bits per sample.
	if (wave_format.numChannels == 1) 
	{
		if (wave_format.bitsPerSample == 8)
			m_format = AL_FORMAT_MONO8;
		else if (wave_format.bitsPerSample == 16)
			m_format = AL_FORMAT_MONO16;
	}
	else if (wave_format.numChannels == 2) 
	{
		if (wave_format.bitsPerSample == 8)
			m_format = AL_FORMAT_STEREO8;
		else if (wave_format.bitsPerSample == 16)
			m_format = AL_FORMAT_STEREO16;
	}

	m_length = (double)m_size / (double)m_frequency;

	alBufferData(m_buffer, m_format, data, m_size, m_frequency);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);
	fin.close();
	auto duration = GetDuration();

	return true;
}

double SoundBuffer::GetDuration()
{
	ALint sizeInBytes;
	ALint channels;
	ALint bits;
	ALint lengthInSamples;
	alGetBufferi(m_buffer, AL_SIZE, &sizeInBytes);
	alGetBufferi(m_buffer, AL_CHANNELS, &channels);
	alGetBufferi(m_buffer, AL_BITS, &bits);

	lengthInSamples = sizeInBytes * 8 / (channels * bits);

	ALint frequency;

	alGetBufferi(m_buffer, AL_FREQUENCY, &frequency);
	return (float)lengthInSamples / (float)frequency;
}
