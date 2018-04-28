#include "aes.h"
#include <string.h>
#include <printf.h>

//__attribute__((section (".mytext")))//隐藏字符表 并没有什么卵用 只是针对初阶hacker的一个小方案而已
char *getKey() {
    int n = 0;
    char s[23];//"NMTIzNDU2Nzg5MGFiY2RlZg";

    s[n++] = 'N';
    s[n++] = 'M';
    s[n++] = 'T';
    s[n++] = 'I';
    s[n++] = 'z';
    s[n++] = 'N';
    s[n++] = 'D';
    s[n++] = 'U';
    s[n++] = '2';
    s[n++] = 'N';
    s[n++] = 'z';
    s[n++] = 'g';
    s[n++] = '5';
    s[n++] = 'M';
    s[n++] = 'G';
    s[n++] = 'F';
    s[n++] = 'i';
    s[n++] = 'Y';
    s[n++] = '2';
    s[n++] = 'R';
    s[n++] = 'l';
    s[n++] = 'Z';
    s[n++] = 'g';
    char *encode_str = s + 1;
    return b64_decode(encode_str, strlen(encode_str));

    //初版hidekey的方案
}

//__attribute__((section (".mytext")))
char *FunEncode(char *str)
{
    uint8_t *AES_KEY = (uint8_t *) getKey();
    char *baseResult = AES_128_ECB_PKCS5Padding_Encrypt(str, AES_KEY);
    return baseResult;
}

char *FunDecode(char *str) {
    uint8_t *AES_KEY = (uint8_t *) getKey();
    char *desResult = AES_128_ECB_PKCS5Padding_Decrypt(str, AES_KEY);
    return desResult;
}

void test_crypto_file()
{
    FILE * pFile = fopen("style.json", "rb");
    if( pFile == NULL )
    {
        return;
    }
    fseek(pFile, 0, SEEK_END);
    int nFileSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    char *pdata =  (char *)malloc(nFileSize + 1);
    fread(pdata, nFileSize, 1, pFile);
    pdata[nFileSize] = 0;
    fclose(pFile);

    char *encodeData = FunEncode(pdata);
    char *decodeData = FunDecode(encodeData);

    FILE *pEncodeFile = fopen("style_encode.dat", "wb");
    if( pEncodeFile != NULL ){
        int len = strlen(encodeData);
        fwrite(encodeData, len, 1, pEncodeFile);
        fflush(pEncodeFile);
        fclose(pEncodeFile);
    }

    FILE *pF = fopen("out.json", "wb");
    if( pF != NULL )
    {
        int len = strlen(decodeData);
        fwrite(decodeData, len, 1, pF);
        fflush(pF);
        fclose(pF);
    }

    free(encodeData);
    free(decodeData);
    free(pdata);
    return;

}

void test_cryto_str()
{
    char *str = "123abcABC*%!~#+_/中文测试";
    char *ecode = "SkiDk/JC5F/BXKf/np7rWNub7ibxzYMjKwkQ7A6AqPw=";

    char *en = FunEncode(str);
    printf("encode : %s", en);
    char *de = FunDecode(en);
    printf("decode :%s", de);
}

int main()
{
    test_crypto_file();
    return 0;

}
