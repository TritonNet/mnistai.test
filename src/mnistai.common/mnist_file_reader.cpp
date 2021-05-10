#include "pch.h"
#include "mnist_file_reader.h"


mnist_file_reader::~mnist_file_reader()
{
    m_images.clear();
}

int mnist_file_reader::reverse_int(int i)
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void mnist_file_reader::read(const char* filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw std::exception("Invalid file name");

    uint32_t magic_number;
    uint32_t num_rows;
    uint32_t num_columns;
    uint32_t num_images;

    file.read((char*)&magic_number, sizeof(magic_number));
    magic_number = reverse_int(magic_number);

    file.read((char*)&num_images, sizeof(num_images));
    num_images = reverse_int(num_images);

    file.read((char*)&num_rows, sizeof(num_rows));
    num_rows = reverse_int(num_rows);

    file.read((char*)&num_columns, sizeof(num_columns));
    num_columns = reverse_int(num_columns);

    m_images.reserve(num_images);

    for (size_t img_idx = 0; img_idx < num_images; img_idx++)
    {
        bitmap_image img(num_rows, num_columns);

        for (size_t row_idx = 0; row_idx < num_rows; row_idx++)
        {
            for (size_t col_idx = 0; col_idx < num_columns; col_idx++)
            {
                unsigned char pixel = 0;
                file.read((char*)&pixel, sizeof(pixel));
                img.set_pixel(row_idx, col_idx, pixel, pixel, pixel);
            }
        }

        m_images.push_back(img);
    }
}
