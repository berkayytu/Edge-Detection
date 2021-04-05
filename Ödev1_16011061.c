#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct pgm {
      int w;
      int h;
      int max;
      char format[100];
      char information[100];
    } pgm;
int fileFail = 0;
    
long int** Read_image_to_matrix(char*, pgm*);
long int** Sobel_filter_x(long int**, long int**, pgm*, char*);
long int** Sobel_filter_y(long int**, long int**, pgm*, char*);
long int** Sobel_filter_final(long int**, long int **, long int**, pgm*, char*);
long int** Normalization(long int**, long int**, pgm*);

int main() {
	char* fileName;
	char temp[20];
	long int** imgMatrix;
	pgm* img;
	int i, j;
	
	printf("Please enter the pgm file with .pgm \n");
	scanf("%s",temp);
	
	fileName = (char *)malloc((strlen(temp)+1)*sizeof(char));
	
	strcpy(fileName,temp);
	
	img = (pgm *) malloc (sizeof(pgm));
	
	imgMatrix = Read_image_to_matrix(fileName,img);
	
	while(!fileFail){
		long int** img_x = (long int **)malloc(img->h * sizeof(long int*));
	
		for(i = 0; i < img->h ; i++){
			img_x[i] = (long int *)malloc(img->w * sizeof(long int));
		}
	
		img_x = Sobel_filter_x(imgMatrix, img_x, img, fileName);
	
		long int** img_y = (long int **)malloc(img->h * sizeof(long int*));
	
		for(i = 0; i < img->h ; i++){
			img_y[i] = (long int *)malloc(img->w * sizeof(long int));
		}
	
		img_y = Sobel_filter_y(imgMatrix, img_y, img, fileName);

		long int** img_final = (long int **)malloc(img->h * sizeof(long int*));
	
		for(i = 0; i < img->h ; i++){
			img_final[i] = (long int *)malloc(img->w * sizeof(long int));
		}
	
		img_final = Sobel_filter_final(img_x, img_y, img_final, img, fileName);
		
		free(img_x);
    	free(img_y);
    	free(img_final);
    	free(imgMatrix);
	}
    
	free(img);
    
	return 0;
}
	


long int** Read_image_to_matrix(char* fileName, pgm* img){
	
	FILE* file = fopen(fileName, "rb"); 
	
	int temp,i,j = 0;
	unsigned char* buffer;
	
	if(!file){
		printf("File %s not found",fileName);
		fileFail = 1;
		return 0;
	}
    
    fgets(img->format, sizeof(img->format), file); //images format
    
    
    fgets(img->information, sizeof(img->format), file); //images information
    
	fscanf (file, "%d", &img->w);
	printf ("images width %d \n", img->w);
	
	fscanf (file, "%d", &img->h);
	printf ("images height %d ", img->h);
	
	fscanf (file, "%d", &img->max); //images the maximum gray value
	
	long int** imgMatrix = (long int **)malloc(img->h * sizeof(long int*));
	
	for(i = 0; i < img->w ; i++){
		imgMatrix[i] = (long int *)malloc(img->w * sizeof(long int));
	}
	
	if(strcmp(img->format,"p5") == 0){
		unsigned char* buffer = (unsigned char*)malloc((img->h * img->w) * sizeof(unsigned char));
		fread((void *) &buffer, sizeof(unsigned char), img->h * img->w, file);
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				imgMatrix[i][j] = (int) buffer[i+j];
			}
		}
	}
	else{
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				fscanf (file, "%d", &imgMatrix[i][j]);
			}
		}
	}	
	
    fclose(file);
    
    return imgMatrix;
}

long int** Sobel_filter_y(long int** imgMatrix, long int** img_y, pgm* img, char* fileName){
	int i, j;
	for(i = 1; i < img->h-1 ; i++){
		for(j = 1; j < img->w-1 ; j++){
			img_y[i][j] = (imgMatrix[i+1][j-1]+2*imgMatrix[i+1][j]+imgMatrix[i+1][j+1]) - (imgMatrix[i-1][j-1]+2*imgMatrix[i-1][j]+imgMatrix[i-1][j+1]);
		}
	}
	
	long int** img_yn = (long int **)malloc(img->h * sizeof(long int*));
	
	for(i = 0; i < img->h ; i++){
		img_yn[i] = (long int *)malloc(img->w * sizeof(long int));
	}
	
	img_yn = Normalization(img_y, img_yn, img);
	
	char y[5] = "_y";
	
	FILE* imgFile_y = fopen(strcat(y,fileName), "w"); 
	
	if(!imgFile_y){
		printf("File %s not found",fileName);
	}
	
	fprintf(imgFile_y,"%s",img->format);
	fprintf(imgFile_y,"%s",img->information);
	fprintf(imgFile_y,"%d ",img->w);
	fprintf(imgFile_y,"%d\n",img->h);
	fprintf(imgFile_y,"%d\n",img->max);
	
	if(strcmp(img->format,"p5") == 0){
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				fwrite((void*)&(img_yn[i][j]),sizeof(unsigned char),1, imgFile_y);
			}
		}	
	}
	else{
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				fprintf(imgFile_y,"%d ", img_yn[i][j]);
			}
		}
	}
	
	fclose(imgFile_y);
	
	return img_y;
}

long int** Sobel_filter_x(long int** imgMatrix, long int** img_x, pgm* img, char* fileName){
	int i,j;
	for(i = 1; i < img->h-1 ; i++){
		for(j = 1; j < img->w-1 ; j++){
			img_x[i][j] = (imgMatrix[i-1][j+1]+2*imgMatrix[i][j+1]+imgMatrix[i+1][j+1]) - (imgMatrix[i-1][j-1]+2*imgMatrix[i][j-1]+imgMatrix[i+1][j-1]);
		}
	}
	
	long int** img_xn = (long int **)malloc(img->h * sizeof(long int*));
	
	for(i = 0; i < img->h ; i++){
		img_xn[i] = (long int *)malloc(img->w * sizeof(long int));
	}
	
	img_xn = Normalization(img_x, img_xn, img);
	
	char x[5] = "_x";
	
	FILE* imgFile_x = fopen(strcat(x,fileName), "w"); 
	
	if(!imgFile_x){
		printf("File %s not found",fileName);
	}
	
	fprintf(imgFile_x,"%s",img->format);
	fprintf(imgFile_x,"%s",img->information);
	fprintf(imgFile_x,"%d ",img->w);
	fprintf(imgFile_x,"%d\n",img->h);
	fprintf(imgFile_x,"%d\n",img->max);
	
	if(strcmp(img->format,"p5") == 0){
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				fwrite((void*)&(img_xn[i][j]),sizeof(unsigned char),1, imgFile_x);
			}
		}	
	}
	else{
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				fprintf(imgFile_x,"%d ", img_xn[i][j]);
			}
		}
	}
	
	fclose(imgFile_x);
	return img_x;
}

long int** Sobel_filter_final(long int** img_x, long int** img_y, long int** img_final, pgm* img, char* fileName){
	int i, j, count = 1;
	for(i = 1; i < (img->h)-1 ; i++){
		for(j = 1; j < (img->w)-1 ; j++){
			img_final[i][j] = sqrt(img_x[i][j] * img_x[i][j] + img_y[i][j] * img_y[i][j]);
		}
	}
	
	long int** img_finaln = (long int **)malloc(img->h * sizeof(long int*));
	
	for(i = 0; i < img->h ; i++){
		img_finaln[i] = (long int *)malloc(img->w * sizeof(long int));
	}
	
	img_finaln = Normalization(img_final, img_finaln, img);
		
	char final[6] = "_final";
	
	FILE* imgFile_final = fopen(strcat(final,fileName), "w"); 
	
	if(!imgFile_final){
		printf("File %s not found",fileName);
	}
	
	fprintf(imgFile_final,"%s",img->format);
	fprintf(imgFile_final,"%s",img->information);
	fprintf(imgFile_final,"%d ",img->w);
	fprintf(imgFile_final,"%d\n",img->h);
	fprintf(imgFile_final,"%d\n",img->max);
	
	if(strcmp(img->format,"p5") == 0){
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				fwrite((void*)&(img_finaln[i][j]),sizeof(unsigned char),1, imgFile_final);
			}
		}	
	}
	else{
		for(i = 0; i < img->h ; i++){
			for(j = 0; j < img->w ; j++){
				if(count % 17 != 0){
				fprintf(imgFile_final,"%d ", img_finaln[i][j]);
				count++;
			}else{
				fprintf(imgFile_final,"%d \n", img_finaln[i][j]);
				count++;
			}
			}
		}
	}

	fclose(imgFile_final);
	return img_x;
}

long int** Normalization(long int** img_nn, long int** img_n, pgm* img){//img_nn mean image non normalized
	int min_ij, max_ij, i, j;
	float temp;
	
	min_ij = img_nn[0][0];
	max_ij = img_nn[0][0]; 
	
	for(i = 0; i < img->h ; i++){
		for(j = 0; j < img->w ; j++){
			if(img_nn[i][j]<min_ij){
				min_ij = img_nn[i][j];
			}
			if(img_nn[i][j]>max_ij){
				max_ij = img_nn[i][j];
			}	
		}
	}
	
	for(i = 0; i < img->h ; i++){
		for(j = 0; j < img->w ; j++){
			temp = (float)(img_nn[i][j] - min_ij)*255;
			temp /= max_ij - min_ij;
			img_n[i][j] = (int) temp;
		}
	}
	
	return img_n;
}

