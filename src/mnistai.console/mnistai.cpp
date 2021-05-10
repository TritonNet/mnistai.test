// mnistai.console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mnistai_cpu.h"
#include "mnist_reader.h"
#include "bitmap_image.hpp"

int main()
{
	try
	{
		std::string MNIST_DATA_LOCATION = "C:\\dev\\opensource\\mnistai.test\\data";

		const auto dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);

		std::cout << "Nbr of training images = " << dataset.training_images.size() << std::endl;
		std::cout << "Nbr of training labels = " << dataset.training_labels.size() << std::endl;
		std::cout << "Nbr of test images = " << dataset.test_images.size() << std::endl;
		std::cout << "Nbr of test labels = " << dataset.test_labels.size() << std::endl;

		for (size_t idx = 0; idx < dataset.training_images.size(); idx++)
		{
			const auto path = MNIST_DATA_LOCATION + "\\images\\" + std::to_string(idx) + ".jpg";

			 bitmap_image(28, 28, dataset.training_images[idx])
				 .save_image(path);

			std::cout << "save image " << std::to_string(idx) << std::endl;
		}
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << "\n";
	}

	std::cin.get();
}