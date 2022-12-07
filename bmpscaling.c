#include<stdio.h>
#include<conio.h>
#include<math.h>
#include"bigtolittleendian.h"
#include"littletobigendian.h"
#include"scaling.h"

typedef struct{
	unsigned char bfType[2];
	unsigned int bfSize;
	unsigned int bfReserved1;
	unsigned int bfReserved2;
	unsigned int bfOffBits;
}bmfh;

typedef struct{
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned int biPlanes;
	unsigned int biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
}bmih;

typedef struct{
    unsigned int biBlue;
    unsigned int biGreen;
    unsigned int biRed;
}acolors[];

//GLOBALS
FILE *fp1,*fp2,*fp3;
unsigned char filename[100]={'0'},buf[4]={'0'};
unsigned char buffer[100]={'0'},rowdata[5]={'0'},temp=0,buffer1=0,headerbuf[10];
unsigned int  colorintensity=0,paletteentrycount=0,i=0,bytestoberead=0,noofshades=0;
unsigned int  zoomfactor=0,ImageSize=0,count=0,readnum=0,writezoomoutnum=0,tmpOff=0;
unsigned int  writezoominnum=0,tmpwritezoominnum=0,tmpreadnum=0,bytesperpel=0;
unsigned int  actHoriSize=0,biHei=0,biWid=0;
//

main()
{
	bmfh fileheader;
	bmih bitmapheader;

	printf("Enter the name of file with extension .bmp (BMP image should be uncompressed):\n");
	scanf("%s",&filename);

    printf("Enter the scaling factor required for output bmp file.\n");
    printf("1. Zoom out the image in both directions.\n");
    printf("2. Zoom in the image from both directions.\n");
    printf("3. Zoom in only Horizontally.\n");
    printf("4. Zoom in only Vertically.\n");
    printf("5. Zoom out only Horizontally.\n");
    printf("6. Zoom out only Vertically.\n");
    scanf("%d",&zoomfactor);
    if(zoomfactor < 1 && zoomfactor > 6)
    {
        printf("Invalid number entered.\n");
        printf("Program terminates.\n");
        return 0;
    }

	fp1=fopen(filename,"rb");
    fp2=fopen("temp.bmp","wb");
    if(fp1==NULL)
    {
        printf("Invalid input filename.\n");
        return 0;
    }

//file header information extraction starts here
    fread (buffer,1,14,fp1);
    fwrite(buffer,1,14,fp2);

    fileheader.bfType[0]    =buffer[0];
    fileheader.bfType[1]    =buffer[1];
    fileheader.bfSize       =littletobig(buffer[2],buffer[3],buffer[4],buffer[5],4);
    fileheader.bfReserved1  =littletobig(buffer[6],buffer[7],0,0,2);
    fileheader.bfReserved2  =littletobig(buffer[8],buffer[9],0,0,2);
    fileheader.bfOffBits    =littletobig(buffer[10],buffer[11],buffer[12],buffer[13],4);

    if(fileheader.bfType[0]!='B' || fileheader.bfType[1]!='M' || 
        fileheader.bfReserved1!=0 || fileheader.bfReserved2!=0)
    {
        printf("Corrupted File Header.\n");
        printf("Terminating Program.....\n");
        goto end;
    }
//file header information extraction ends

    printf("BMP HEADER INFORMATION:\n");
    printf("\t %-25s: %c%c\n","File Type",fileheader.bfType[0],fileheader.bfType[1]);
    printf("\t %-25s: %d\n",  "File Size",fileheader.bfSize);
    printf("\t %-25s: %d\n",  "Reserved Bit 1",fileheader.bfReserved1);
    printf("\t %-25s: %d\n",  "Reserved Bit 2",fileheader.bfReserved2);
    printf("\t %-25s: %d\n",  "File Offset for Data",fileheader.bfOffBits);

//bitmap header information extraction starts here
    if((fileheader.bfOffBits-14)<=100)
    {
        fread (buffer,1,fileheader.bfOffBits-14,fp1);
        fwrite(buffer,1,fileheader.bfOffBits-14,fp2);
    }
    else
    {
        fread (buffer,1,40,fp1);
        fwrite(buffer,1,40,fp2);

        tmpOff=fileheader.bfOffBits-54;
        while(tmpOff>0)
        {
            fread (headerbuf,1,1,fp1);
            fwrite(headerbuf,1,1,fp2);
            tmpOff--;
        }
    }

    bitmapheader.biSize         =littletobig(buffer[0],buffer[1],buffer[2],buffer[3],4);
    bitmapheader.biWidth        =littletobig(buffer[4],buffer[5],buffer[6],buffer[7],4);
    bitmapheader.biHeight       =littletobig(buffer[8],buffer[9],buffer[10],buffer[11],4);
    bitmapheader.biPlanes       =littletobig(buffer[12],buffer[13],0,0,2);
    bitmapheader.biBitCount     =littletobig(buffer[14],buffer[15],0,0,2);
    bitmapheader.biCompression  =littletobig(buffer[16],buffer[17],buffer[18],buffer[19],4);
    bitmapheader.biSizeImage    =littletobig(buffer[20],buffer[21],buffer[22],buffer[23],4);
    bitmapheader.biXPelsPerMeter=littletobig(buffer[24],buffer[25],buffer[26],buffer[27],4);
    bitmapheader.biYPelsPerMeter=littletobig(buffer[28],buffer[29],buffer[30],buffer[31],4);   
    bitmapheader.biClrUsed      =littletobig(buffer[32],buffer[33],buffer[34],buffer[35],4);
    bitmapheader.biClrImportant =littletobig(buffer[36],buffer[37],buffer[38],buffer[39],4);
//bitmap header information extraction ends here

    printf("\n");
    printf("BITMAP HEADER INFORMATION:\n");
    printf("\t %-25s: %d\n",  "Bitmap Header Size",bitmapheader.biSize);
    printf("\t %-25s: %d\n",  "Image Width",bitmapheader.biWidth);
    printf("\t %-25s: %d\n",  "Image Height",bitmapheader.biHeight);
    printf("\t %-25s: %d\n",  "Number of Planes",bitmapheader.biPlanes);
    printf("\t %-25s: %d\n",  "Number of Bits per Pel",bitmapheader.biBitCount);
        
    if(bitmapheader.biCompression==0)
        printf("\t %-25s: %d(%s)\n",  "Compression Type",bitmapheader.biCompression,"Uncompressed Data");
    else if (bitmapheader.biCompression==1)
        printf("\t %-25s: %d(%s)\n",  "Compression Type",bitmapheader.biCompression,"RGB_8");
    else if (bitmapheader.biCompression==2)
        printf("\t %-25s: %d(%s)\n",  "Compression Type",bitmapheader.biCompression,"RGB_4");
    else if (bitmapheader.biCompression==3)
        printf("\t %-25s: %d(%s)\n",  "Compression Type",bitmapheader.biCompression,"RGB bitmap with MASK");

    printf("\t %-25s: %d\n",  "Size of Image",bitmapheader.biSizeImage);
    printf("\t %-25s: %d\n",  "X Pixels per Meter",bitmapheader.biXPelsPerMeter);
    printf("\t %-25s: %d\n",  "Y Pixels per Meter",bitmapheader.biYPelsPerMeter);
    printf("\t %-25s: %d\n",  "Colours Used",bitmapheader.biClrUsed);
    printf("\t %-25s: %d\n",  "Colours Important",bitmapheader.biClrImportant);

    ImageSize=bitmapheader.biSizeImage;
    
    bytesperpel     =bitmapheader.biBitCount/8;
    biHei           =bitmapheader.biHeight;
    biWid           =bitmapheader.biWidth;
    readnum         =(int)(4*ceil((double)(bitmapheader.biWidth*bytesperpel)/4));
    writezoomoutnum =(int)(4*ceil((double)(bitmapheader.biWidth*bytesperpel)/8));
    writezoominnum  =(int)(4*ceil((double)(bitmapheader.biWidth*bytesperpel)/2));
    tmpreadnum      =readnum;
    actHoriSize     =readnum;
    
    
	if((bitmapheader.biBitCount==32 || bitmapheader.biBitCount==24 
        || bitmapheader.biBitCount==16 || bitmapheader.biBitCount==8) &&
        bitmapheader.biCompression==0)
	{
	    if(zoomfactor==1)
	    {
            zoomout();
        }
        else if (zoomfactor==2)
        {
            zoomin();
        }
        else if (zoomfactor==3)
        {
            horizontalzoomin();
        }
        else if (zoomfactor==4)
        {
            verticalzoomin();
        }
        else if (zoomfactor==5)
        {
            horizontalzoomout();
        }
        else if (zoomfactor==6)
        {
            verticalzoomout();
        }
    }
    	else if (bitmapheader.biBitCount==4 && bitmapheader.biCompression==0)
	{
        if(zoomfactor==1)
	    {
            zoomoutbit4();
        }
        else if (zoomfactor==2)
        {
            zoominbit4();
        }
        else if (zoomfactor==3)
        {
            horizontalzoominbit4();
        }
        else if (zoomfactor==4)
        {
            verticalzoominbit4();
        }
        else if (zoomfactor==5)
        {
            horizontalzoomoutbit4();
        }
        else if (zoomfactor==6)
        {
            verticalzoomoutbit4();
        }
    }
    else if (bitmapheader.biBitCount==1 && bitmapheader.biCompression==0)
	{
        if(zoomfactor==1)
	    {
            zoomoutbit();
        }
        else if (zoomfactor==2)
        {
            zoominbit();
        }
        else if (zoomfactor==3)
        {
            horizontalzoominbit();
        }
        else if (zoomfactor==4)
        {
            verticalzoominbit();
        }
        else if (zoomfactor==5)
        {
            horizontalzoomoutbit();
        }
        else if (zoomfactor==6)
        {
            verticalzoomoutbit();
        }
    }

    fclose(fp1);
	fclose(fp2);

    printf("Wait...\n");
    fp2=fopen("temp.bmp","rb");
    fp3=fopen("scaled.bmp","wb");
	fread(buffer,1,fileheader.bfOffBits,fp2);
    if(zoomfactor==1)
    {
        bitmapheader.biSizeImage=bitmapheader.biSizeImage/4;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[34]=buf[0];
        buffer[35]=buf[1];
        buffer[36]=buf[2];
        buffer[37]=buf[3];

        bitmapheader.biWidth=bitmapheader.biWidth/2;
        bigtolittle(bitmapheader.biWidth);
        buffer[18]=buf[0];
        buffer[19]=buf[1];
        buffer[20]=buf[2];
        buffer[21]=buf[3];

        bitmapheader.biHeight=bitmapheader.biHeight/2;
        bigtolittle(bitmapheader.biHeight);
        buffer[22]=buf[0];
        buffer[23]=buf[1];
        buffer[24]=buf[2];
        buffer[25]=buf[3];        

        bitmapheader.biSizeImage=bitmapheader.biSizeImage+fileheader.bfOffBits;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[2]=buf[0];
        buffer[3]=buf[1];
        buffer[4]=buf[2];
        buffer[5]=buf[3]; 
    }
    else if (zoomfactor==2)
    {
        bitmapheader.biSizeImage=bitmapheader.biSizeImage*4;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[34]=buf[0];
        buffer[35]=buf[1];
        buffer[36]=buf[2];
        buffer[37]=buf[3];

        bitmapheader.biWidth=bitmapheader.biWidth*2;
        bigtolittle(bitmapheader.biWidth);
        buffer[18]=buf[0];
        buffer[19]=buf[1];
        buffer[20]=buf[2];
        buffer[21]=buf[3];

        bitmapheader.biHeight=bitmapheader.biHeight*2;
        bigtolittle(bitmapheader.biHeight);
        buffer[22]=buf[0];
        buffer[23]=buf[1];
        buffer[24]=buf[2];
        buffer[25]=buf[3]; 

        bitmapheader.biSizeImage=bitmapheader.biSizeImage+fileheader.bfOffBits;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[2]=buf[0];
        buffer[3]=buf[1];
        buffer[4]=buf[2];
        buffer[5]=buf[3]; 
    }
    else if (zoomfactor==3)
    {
        bitmapheader.biSizeImage=bitmapheader.biSizeImage*2;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[34]=buf[0];
        buffer[35]=buf[1];
        buffer[36]=buf[2];
        buffer[37]=buf[3];

        bitmapheader.biWidth=bitmapheader.biWidth*2;
        bigtolittle(bitmapheader.biWidth);
        buffer[18]=buf[0];
        buffer[19]=buf[1];
        buffer[20]=buf[2];
        buffer[21]=buf[3];

        bitmapheader.biSizeImage=bitmapheader.biSizeImage+fileheader.bfOffBits;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[2]=buf[0];
        buffer[3]=buf[1];
        buffer[4]=buf[2];
        buffer[5]=buf[3]; 
    }
    else if (zoomfactor==4)
    {
        bitmapheader.biSizeImage=bitmapheader.biSizeImage*2;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[34]=buf[0];
        buffer[35]=buf[1];
        buffer[36]=buf[2];
        buffer[37]=buf[3];

        bitmapheader.biHeight=bitmapheader.biHeight*2;
        bigtolittle(bitmapheader.biHeight);
        buffer[22]=buf[0];
        buffer[23]=buf[1];
        buffer[24]=buf[2];
        buffer[25]=buf[3]; 

        bitmapheader.biSizeImage=bitmapheader.biSizeImage+fileheader.bfOffBits;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[2]=buf[0];
        buffer[3]=buf[1];
        buffer[4]=buf[2];
        buffer[5]=buf[3]; 
    }
    else if(zoomfactor==5)
    {
        bitmapheader.biSizeImage=bitmapheader.biSizeImage/2;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[34]=buf[0];
        buffer[35]=buf[1];
        buffer[36]=buf[2];
        buffer[37]=buf[3];

        bitmapheader.biWidth=bitmapheader.biWidth/2;
        bigtolittle(bitmapheader.biWidth);
        buffer[18]=buf[0];
        buffer[19]=buf[1];
        buffer[20]=buf[2];
        buffer[21]=buf[3];

        bitmapheader.biSizeImage=bitmapheader.biSizeImage+fileheader.bfOffBits;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[2]=buf[0];
        buffer[3]=buf[1];
        buffer[4]=buf[2];
        buffer[5]=buf[3]; 
    }
    else if(zoomfactor==6)
    {
        bitmapheader.biSizeImage=bitmapheader.biSizeImage/2;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[34]=buf[0];
        buffer[35]=buf[1];
        buffer[36]=buf[2];
        buffer[37]=buf[3];

        bitmapheader.biHeight=bitmapheader.biHeight/2;
        bigtolittle(bitmapheader.biHeight);
        buffer[22]=buf[0];
        buffer[23]=buf[1];
        buffer[24]=buf[2];
        buffer[25]=buf[3];        

        bitmapheader.biSizeImage=bitmapheader.biSizeImage+fileheader.bfOffBits;
        bigtolittle(bitmapheader.biSizeImage);
        buffer[2]=buf[0];
        buffer[3]=buf[1];
        buffer[4]=buf[2];
        buffer[5]=buf[3]; 
    }

    fwrite(buffer,1,fileheader.bfOffBits,fp3);

    bitmapheader.biSizeImage=bitmapheader.biSizeImage-fileheader.bfOffBits;

    if((bitmapheader.biBitCount==32 || bitmapheader.biBitCount==24 
        || bitmapheader.biBitCount==16 || bitmapheader.biBitCount==8) &&
        bitmapheader.biCompression==0)
    {
        tmpreadnum=bitmapheader.biSizeImage*bytesperpel;
    }
    else if (bitmapheader.biBitCount==1 && bitmapheader.biCompression==0)
    {
        tmpreadnum=bitmapheader.biSizeImage;
    }
    while(tmpreadnum>0)
    {
        fread(buffer,1,1,fp2);
        fwrite(buffer,1,1,fp3);
        tmpreadnum--;        
    }
    
	fclose(fp2);
    fclose(fp3);
end:;
    return 0;
}