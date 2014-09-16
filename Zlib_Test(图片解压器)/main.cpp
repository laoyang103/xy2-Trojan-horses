
#include "MyCompress.h"

int main() {
	MyCompress mycom;

    unsigned long fsize, foutsize;
    char* fdata;
    char* fout;
   
    FILE *fp = fopen("temp.yao", "rb");
	if(!fp)
	{
		printf("�������˳���ԭ��û���ҵ�temp.yao�ļ�\n�뽫����������һ��\n");
		return -1;
	}

    {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fdata = (char*)malloc(fsize);
        fread(fdata, fsize, 1, fp);
        foutsize = mycom.zlib_uncompress_size(fdata, fsize);
        fout  = (char*)malloc(foutsize);
        fclose(fp);
    }

    mycom.zlib_uncompress(fout, &foutsize, fdata, fsize);
    {
        fp = fopen("temp1.bmp", "wb");
        if (fp) {
            fwrite(fout, foutsize, 1, fp);
        } else {

            printf("write file temp1.bmp ERROR\n");
            fflush(stdout);

            return -2;
        }
        fclose(fp);
		printf("��������ɣ�");
    }

    getchar();
    return 0;
}