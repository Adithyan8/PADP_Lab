#include<stdio.h>
#include<gd.h>
#include<omp.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
    char *iname = argv[1];
    char *oname = argv[2];
    int x,y,color,red,green,blue,temp;
    FILE *fin = fopen(iname,"r");
    if(fin==NULL)
    {
        printf("Error : Unable to open file\n");
        exit(0);
    }
    gdImagePtr img = gdImageCreateFromPng(fin);
    int w = gdImageSX(img),h = gdImageSY(img);

    double start = omp_get_wtime();
    omp_set_num_threads(4);
    #pragma omp parallel for private(y,color,red,green,blue) schedule(static,50) //schedule(dynamic,50) schedule(guided,50)
    for(x=0;x<w;x++)
    {
        for(y=0;y<h;y++)
        {
            color = gdImageGetPixel(img,x,y);
            red = gdImageRed(img,color);
            blue = gdImageBlue(img,color);
            green = gdImageGreen(img,color);
            temp = (red+green+blue)/3;

            color = gdImageColorAllocate(img,temp,temp,temp);
            gdImageSetPixel(img,x,y,color);
        }
    }
    double end = omp_get_wtime();
    printf("Time taken with 4 threads : %lf\n",end-start);

    FILE fop = fopen(oname,"w");
    if(fop == NULL)
    {
        printf("Error : File cannot be opened\n");
        exit(0);
    }
    gdImagePng(img,fop);
    fclose(fop);
    fclose(fin);
    gdImageDestroy(img);
    return 0;
}