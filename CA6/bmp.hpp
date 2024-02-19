#ifndef BMP_HPP_INCLUDE
#define BMP_HPP_INCLUDE

#include <cstdint>
#include <string>
#include <vector>

#pragma pack(push, 1)
struct Header {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};
struct InfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

constexpr uint16_t BMP_FILE_TYPE = 0x4D42;

struct Pixel {
    Pixel() = default;

    Pixel(uint8_t r, uint8_t g, uint8_t b);

    uint8_t blu;
    uint8_t grn;
    uint8_t red;
};

struct Bmp {
    char *fileData = nullptr;
    bool validState = false;
    Header hdr;
    InfoHeader infoHdr;
    int padding;
    std::vector<std::vector<Pixel>> data;
};

enum class ReadResult {
    success,
    open_err,
    invalid_file,
    unsupported_bmp,
    alloc_err,
};

class BMP {
public:
    static bool create(Bmp &bmp, int width, int height);

    static ReadResult read(Bmp &bmp, const std::string &filename);

    static bool write(Bmp &bmp, const std::string &filename);

    static int calcBmpPadding(int width);

    static Pixel &getFilePixel(const Bmp &bmp, int row, int col);

    static void fileDataToVector(Bmp &bmp);

    static void vectorToFileData(Bmp &bmp);
};

#endif // BMP_HPP_INCLUDE
