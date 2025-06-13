#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct image {
    char MagicNum[50];
    char comment[100];
    int width;
    int height;
    int depth;
    unsigned char **img;
} IMAGE;

enum flip {
    LEFT_RIGHT,
    TOP_BOTTOM
};

enum size {
    DOUBLE_SIZE,
    HALF_SIZE
};

void readPGMHeader(FILE *file, IMAGE *image) {
    fgets(image -> MagicNum, sizeof(image -> MagicNum), file);
    fgets(image -> comment, sizeof(image -> comment), file);
    fscanf(file, "%d %d", &image -> width, &image -> height);
    fscanf(file, "%d", &image -> depth);
    fgetc(file);
}

void readPGMPixels(FILE *file, IMAGE *image) {
    int j, k;
    image -> img = (unsigned char **)malloc(image -> height * sizeof(unsigned char *));
    if(!image -> img) {
        perror("메모리 할당 실패"); exit(EXIT_FAILURE);
    }
    for(j = 0; j < image -> height; j++) {
        image -> img[j] = (unsigned char *)malloc(image -> width * sizeof(unsigned char));
        if(!image -> img[j]) { 
            perror("메모리 할당 실패"); 
            for(k = 0; k < j; k++) {
                free(image -> img[k]);
            }
            free(image -> img);
            exit(EXIT_FAILURE); 
        }
    }
    for(j = 0; j < image -> height; j++) {
        fread(image -> img[j], sizeof(unsigned char), image -> width, file);
    }
}

void writePGM(FILE *file, IMAGE *image) {
    int i;
    fprintf(file, "%s", image -> MagicNum);
    fprintf(file, "%s", image -> comment);
    fprintf(file, "%d %d\n", image -> width, image -> height);
    fprintf(file, "%d\n", image -> depth);
    for(i = 0; i < image -> height; i++) {
        fwrite(image -> img[i], sizeof(unsigned char), image -> width, file);
    }
}

void freeImagePixels(IMAGE *image) {
    int i;
    if(image && image -> img) {
        for(i = 0; i < image -> height; i++) {
            free(image -> img[i]);
            image -> img[i] = NULL;
        }
        free(image -> img);
        image -> img = NULL;
    }
}

void FindEdge(IMAGE* input, IMAGE* output) {
    int i, j;
    short **garo = (short **)malloc(input -> height * sizeof(short *));
    short **sero = (short **)malloc(input -> height * sizeof(short *));
    for (i = 0; i < input -> height; i++) {
        garo[i] = (short *)malloc(input -> width * sizeof(short));
        sero[i] = (short *)malloc(input -> width * sizeof(short));
    }

    for (i = 0; i < input -> height; i++) {
        for (j = 0; j < input -> width; j++) {
            garo[i][j] = (j < input -> width - 1) ? input -> img[i][j+1] - input -> img[i][j] : 0;
            sero[i][j] = (i < input -> height - 1) ? input -> img[i+1][j] - input -> img[i][j] : 0;
        }
    }

    for (i = 0; i < input -> height; i++) {
        for (j = 0; j < input -> width; j++) {
            double val = sqrt(pow(garo[i][j], 2) + pow(sero[i][j], 2));
            output -> img[i][j] = (unsigned char)((val > 255) ? 255 : ((val < 0) ? 0 : val));
        }
    }

    for (i = 0; i < input -> height; i++) { 
        free(garo[i]); 
        free(sero[i]);
    }
    free(garo);
    free(sero);
}

void ImageBrightness(unsigned char** input, unsigned char** output, int width, int height, int value) {
    int i, j;
    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            int newValue = input[i][j] + value;
            output[i][j] = (unsigned char)((newValue < 0) ? 0 : ((newValue > 255) ? 255 : newValue));
        }
    }
}

void ImageTransformation(unsigned char** input, unsigned char** output, int width, int height, enum flip mode) {
    int i, j;
    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if(mode == LEFT_RIGHT) {
                output[i][j] = input[i][width - 1 - j];
            }
            else if(mode == TOP_BOTTOM) {
                output[i][j] = input[height - 1 - i][j];
            }
            else {
                output[i][j] = input[i][j];
            }
        }
    }
}

void ImageSizeChange(unsigned char** input, unsigned char** output, int input_width, int input_height, int output_width, int output_height, float ratio) {
    int i, j;
    for(i = 0; i < output_height; i++) {
        for(j = 0; j < output_width; j++) {
            if(ratio == 2.0) {
                output[i][j] = input[i / 2][j / 2];
            }
            else if(ratio == 0.5) {
                output[i][j] = input[i * 2][j * 2];
            }
            else if(i < input_height && j < input_width) {
                output[i][j] = input[i][j];
            }
        }
    }
}

int main(void) {
    FILE *inputFile, *outputFile;
    IMAGE image_in, image_out;
    int choice, param_value, new_width, new_height;
    float size_ratio; 
    char fname[50];
    char fpath[100] = "\"C:\\Program Files\\IrfanView\\i_view64.exe\" ";
    char n1_fpath[200];

    printf("원본 PGM 파일의 이름: ");
    scanf("%s", fname);

    inputFile = fopen(fname, "rb");
    if(!inputFile) { 
        perror("원본 파일을 열 수 없습니다"); 
        return 1; 
    }

    readPGMHeader(inputFile, &image_in);
    readPGMPixels(inputFile, &image_in);
    fclose(inputFile);

    image_out.width = image_in.width;
    image_out.height = image_in.height;
    image_out.depth = image_in.depth;
    strcpy(image_out.MagicNum, image_in.MagicNum);
    strcpy(image_out.comment, image_in.comment);

    printf("\n");
    printf("영상 처리 메뉴\n");
    printf("===============\n");
    printf("1. 밝기 조절\n");
    printf("2. 좌우/상하 대칭 변환\n");
    printf("3. 영상 크기 조절 (2배 확대 또는 1/2 축소)\n");
    printf("4. 에지 검출\n");
    printf("===============\n");
    printf("메뉴 선택: ");
    scanf("%d", &choice);

    new_width = image_in.width; new_height = image_in.height;

    switch(choice) {
        case 1: {
            printf("밝기를 조절할 값을 입력하세요 (+값: 밝게, -값: 어둡게): "); scanf("%d", &param_value); 
        } break;
        case 2: {
            printf("변환 모드를 선택하세요 (0: 좌우대칭, 1: 상하대칭): "); scanf("%d", &param_value); 
        } break;
        case 3: {
            printf("영상의 크기를 입력하세요 (2: 2배 확대, 0.5: 1/2 축소): "); scanf("%f", &size_ratio);
            new_width = (size_ratio == 2.0) ? image_in.width * 2 : (size_ratio == 0.5) ? image_in.width / 2 : image_in.width;
            new_height = (size_ratio == 2.0) ? image_in.height * 2 : (size_ratio == 0.5) ? image_in.height / 2 : image_in.height;
            if (new_width < 1) new_width = 1; if (new_height < 1) new_height = 1;
            image_out.width = new_width; image_out.height = new_height; 
        } break;
        case 4: { 
            printf("에지 검출 중...\n"); 
        } break;
        default: {
            printf("잘못된 선택입니다. 원본 이미지를 그대로 저장합니다.\n"); 
        } break;
    }

    image_out.img = (unsigned char **)malloc(new_height * sizeof(unsigned char *));
    if(!image_out.img) {
        perror("출력 이미지 메모리 할당 실패\n"); freeImagePixels(&image_in); 
        return 1; 
    }
    for(int i = 0; i < new_height; i++) {
        image_out.img[i] = (unsigned char *)malloc(new_width * sizeof(unsigned char));
        if(!image_out.img[i]) { 
            perror("출력 이미지 메모리 할당 실패\n"); 
            for (int k = 0; k < i; k++) {
                free(image_out.img[k]);
            }
            free(image_out.img);
            freeImagePixels(&image_in); 
            return 1; 
        }
    }

    switch(choice) {
        case 1: {
            ImageBrightness(image_in.img, image_out.img, image_in.width, image_in.height, param_value); 
        } break;
        case 2: {
            ImageTransformation(image_in.img, image_out.img, image_in.width, image_in.height, (enum flip)param_value); 
        } break;
        case 3: { 
            ImageSizeChange(image_in.img, image_out.img, image_in.width, image_in.height, new_width, new_height, size_ratio); 
        } break;
        case 4: {
            FindEdge(&image_in, &image_out);
        } break;
        default: {
            for (int i = 0; i < image_in.height; i++) {
                memcpy(image_out.img[i], image_in.img[i], image_in.width * sizeof(unsigned char)); 
            }
        } break;
    }

    outputFile = fopen("output.pgm", "wb");
    if(!outputFile) { 
        perror("저장 파일을 열 수 없습니다");
        freeImagePixels(&image_in); 
        freeImagePixels(&image_out); 
        return 1; 
    }
    writePGM(outputFile, &image_out);
    fclose(outputFile);

    freeImagePixels(&image_in);
    freeImagePixels(&image_out);

    printf("이미지 처리가 완료되었습니다. 'output.pgm' 파일을 확인하세요.\n");
    printf("IrfanView 프로그램으로 'output.pgm' 파일을 자동 실행합니다.\n");
    snprintf(n1_fpath, sizeof(n1_fpath), "%soutput.pgm", fpath);
    if(system(n1_fpath) != 0) {
        printf("IrfanView 실행 중 오류 발생. IrfanView 설치 경로(\"C:\\Program Files\\IrfanView\\i_view64.exe\")가 올바른지 확인하십시오.\n");
    }

    return 0;
}
