#include "mnist.h"

#define MNIST_TRAINING_IMAGES_PATH "data/t10k-images.idx3-ubyte"
#define MNIST_TRAINING_LABELS_PATH "data/t10k-labels.idx1-ubyte"

#define MNIST_LABEL_MAGIC 0x00000801
#define MNIST_IMAGE_MAGIC 0x00000803
#define MNIST_LABELS 10

struct MnistLabelsFileHeader {
    const uint32_t magic_number;
    const uint32_t number_of_labels;
} MnistLabelsFileHeader;

struct MnistImagesFileHeader {
    const uint32_t magic_number;
    const uint32_t number_of_images;
    const uint32_t number_of_rows;
    const uint32_t number_of_columns;
} MnistImagesFileHeader;

uint32_t map_uint32(uint32_t in)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return (
        ((in & 0xFF000000) >> 24) |
        ((in & 0x00FF0000) >>  8) |
        ((in & 0x0000FF00) <<  8) |
        ((in & 0x000000FF) << 24)
    );
#else
    return in;
#endif
}

const ImageDset * get_training_dataset() {
    char *image_stream = read_file(MNIST_TRAINING_IMAGES_PATH);
    char *label_stream = read_file(MNIST_TRAINING_LABELS_PATH);

    if (!image_stream || !label_stream) return NULL;

    /* read the labels file header */
    struct MnistLabelsFileHeader *labels_file_header = (struct MnistLabelsFileHeader *) label_stream;
    label_stream += sizeof(MnistLabelsFileHeader);

    /* make sure the labels file header is as expected */
    uint32_t magic_num = map_uint32(labels_file_header->magic_number);
    if (magic_num != MNIST_LABEL_MAGIC) return NULL;

    /* read the image file header */
    struct MnistImagesFileHeader  *images_file_header = (struct MnistImagesFileHeader *) image_stream;
    image_stream += sizeof(MnistImagesFileHeader);

    /* make sure the image file header is as expected */
    magic_num = map_uint32(images_file_header->magic_number);
    if (magic_num != MNIST_IMAGE_MAGIC) return NULL;

    /* build the dataset */
    const size_t num_images = map_uint32(images_file_header->number_of_images);
    const size_t x_len = map_uint32(images_file_header->number_of_columns);
    const size_t y_len = map_uint32(images_file_header->number_of_rows);

    const size_t bitmap_size = x_len * y_len;

    Image * images_init = xmalloc(sizeof(Image) * num_images);
    for (size_t i = 0; i < num_images; i++) {
        /* read next image label */
        images_init[i].label = *label_stream;
        label_stream++;

        /* read next image bitmap */
        images_init[i].bitmap = bitmap_init(image_stream, x_len, y_len);
        image_stream += bitmap_size;
    }

    const Image * images = xmalloc(sizeof(Image) * num_images);
    memcpy(images, images_init, sizeof(Image) * num_images);

    ImageDset dataset_init = {
        .len = num_images,
        .x_len = x_len,
        .y_len = y_len,
        .images = images
    };
    const ImageDset * dataset = xmalloc(sizeof(ImageDset));
    memcpy(dataset, &dataset_init, sizeof *dataset);

    return dataset;
}

void mnist_test() {
    const ImageDset * dataset = get_training_dataset();
    if (dataset != NULL) {
        printf("Passed ");
    } else {
        printf("Failed ");
    }
    printf("mnist_test\n");
    printf("First label %d\n", dataset->images[15].label);
}