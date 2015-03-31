// ±àÒë×Ö·û±í
static unsigned char base64encode_lut[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// ½âÊÍ×Ö·û±í
char base64decode_lut[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,62, 0, 0, 0,63,52,53,54,55,56,57,58,59,60,61, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
    15,16,17,18,19,20,21,22,23,24,25, 0, 0, 0, 0, 0, 0,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,
    49,50,51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

void base64encode(char *src, char *dest, int len){// Ö´ÐÐBase64±àÂë
    int i=0, slen=strlen(src);
    for(i=0;i<slen && i<len;i+=3,src+=3) { 
        *(dest++)=base64encode_lut[(*src&0xFC)>>0x2];
        *(dest++)=base64encode_lut[(*src&0x3)<<0x4|(*(src+1)&0xF0)>>0x4];
        *(dest++)=((i+1)<slen)?base64encode_lut[(*(src+1)&0xF)<<0x2|(*(src+2)&0xC0)>>0x6]:'=';
        *(dest++)=((i+2)<slen)?base64encode_lut[*(src+2)&0x3F]:'=';
    }
    *dest='\0';
}

void base64decode(char *src, char *dest, int len){// Ö´ÐÐBase64½âÂë
    int i=0, slen=strlen(src);
    for(i=0;i<slen&&i<len;i+=4,src+=4) {
        char c1=base64decode_lut[*src], c2=base64decode_lut[*(src+1)], c3=base64decode_lut[*(src+2)], c4=base64decode_lut[*(src+3)];
        *(dest++)=(c1&0x3F)<<0x2|(c2&0x30)>>0x4;
        *(dest++)=(c3!=64)?((c2&0xF)<<0x4|(c3&0x3C)>>0x2):'\0';
        *(dest++)=(c4!=64)?((c3&0x3)<<0x6|c4&0x3F):'\0';
    }
    *dest='\0';
}
// ¶Ô×Ö·û´®½øÐÐbase64±àÒë
int b64_encode_string( char *source, char *lrvar ){
    int dest_size;
    int res;
    char *dest;
    dest_size = 1 + ((strlen(source)+2)/3*4);
    dest = (char *)malloc(dest_size);
    memset(dest,0,dest_size);
    base64encode(source, dest, dest_size);
    lr_save_string( dest, lrvar );
    res = strlen(dest);
    free(dest);
    return res;
}

int b64_decode_string( char *source, char *lrvar ){// ½âÂëbase64×Ö·û´®
    int dest_size;
    int res;
    char *dest;
    dest_size = strlen(source);
    dest = (char *)malloc(dest_size);
    memset(dest,0,dest_size);
    base64decode(source, dest, dest_size);
    lr_save_string( dest, lrvar );
    res = strlen(dest);
    free(dest);
    return res;
}
