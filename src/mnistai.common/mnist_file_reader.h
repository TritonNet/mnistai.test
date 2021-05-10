#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "bitmap_image.hpp"

class mnist_file_reader
{
public:
	~mnist_file_reader();
	void read(const char* filename);
	size_t get_num_images() { return m_images.size(); }
	std::vector<bitmap_image>& images() { return m_images; }

private:
	int reverse_int(int i);
	std::vector<bitmap_image> m_images;
};

