#include <gtest/gtest.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16
unsigned char global_key[BLOCK_SIZE];

// Mismo código que antes, pero copiado aquí directamente
void aes_cbc_encrypt(const unsigned char *in, unsigned char *out, const unsigned char *key, unsigned char *iv, int len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cbc_encrypt(in, out, len, &enc_key, iv, AES_ENCRYPT);
}

void pkcs7_padding(unsigned char *data, int len, int *padded_len) {
    int padding = BLOCK_SIZE - (len % BLOCK_SIZE);
    for (int i = 0; i < padding; i++) {
        data[len + i] = padding;
    }
    *padded_len = len + padding;
}

void random_bytes(unsigned char *buf, int len) {
    for (int i = 0; i < len; i++) buf[i] = rand() % 256;
}

// TESTS
TEST(AESCBC, EncryptDecrypt) {
    unsigned char plaintext[BLOCK_SIZE] = "hello world";
    unsigned char ciphertext[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE] = {0};

    aes_cbc_encrypt(plaintext, ciphertext, global_key, iv, BLOCK_SIZE);

    EXPECT_TRUE(memcmp(plaintext, ciphertext, BLOCK_SIZE) != 0);
}

TEST(PaddingTest, CorrectPadding) {
    unsigned char data[32] = "test";
    int padded_len = 0;

    pkcs7_padding(data, 4, &padded_len);
    EXPECT_EQ(padded_len, 16);
}

TEST(RandomBytesTest, GeneratesDifferentValues) {
    unsigned char buf1[BLOCK_SIZE], buf2[BLOCK_SIZE];
    random_bytes(buf1, BLOCK_SIZE);
    random_bytes(buf2, BLOCK_SIZE);
    EXPECT_TRUE(memcmp(buf1, buf2, BLOCK_SIZE) != 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
