FILE *fp1,*fp2,*fp3;
extern unsigned char filename[100];
extern unsigned char buffer[100],rowdata[5],temp,buffer1,headerbuf[10];
extern unsigned int colorintensity,paletteentrycount,i,bytestoberead,noofshades;
extern unsigned int zoomfactor,ImageSize,count,readnum,writezoomoutnum,tmpOff,actHoriSize;
extern unsigned int writezoominnum,tmpwritezoominnum,tmpreadnum,bytesperpel,biHei,biWid;

zoomout()
{
    while(ImageSize>0)
    {
        fread(buffer,1,bytesperpel,fp1);
	    fread(buffer,1,bytesperpel,fp1);            
	    fwrite(buffer,1,bytesperpel,fp2);
        readnum=readnum-(bytesperpel*2);
        writezoomoutnum=writezoomoutnum-bytesperpel;
        ImageSize=ImageSize-(bytesperpel*2);
	    count++;
        if(count==biWid/2)
	    {
            while(writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }
            if(ImageSize==0)
            {
                break;
            }
	        
            fseek(fp1,actHoriSize,SEEK_CUR);//skip one row
            ImageSize=ImageSize-actHoriSize;
            
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
            writezoomoutnum=(int)(4*ceil((double)(biWid*bytesperpel)/8));
	    }
    }
    printf("EOF.....\n");
    return 0;
}
 
zoomin()
{
    while(ImageSize>0)
    {
        fread(buffer,1,bytesperpel,fp1);
	    fwrite(buffer,1,bytesperpel,fp2);
	    fwrite(buffer,1,bytesperpel,fp2);
        readnum=readnum-bytesperpel;
        writezoominnum=writezoominnum-(bytesperpel*2);
        ImageSize=ImageSize-bytesperpel;
        count++;
	    
	    if(count==biWid)
	    {
            tmpwritezoominnum=writezoominnum;
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
	        fseek(fp1,-(biWid*bytesperpel),SEEK_CUR);
	        while(count>0)
	        {
	            fread(rowdata,1,bytesperpel,fp1);
	            fwrite(rowdata,1,bytesperpel,fp2);
	            fwrite(rowdata,1,bytesperpel,fp2);
	            count--;
	        }
            while(tmpwritezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                tmpwritezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }
            if(ImageSize==0)
            {
                break;
            }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
            writezoominnum=(int)(4*ceil((double)(biWid*bytesperpel)/2));
	    }
    }
    printf("EOF.......\n");
                
    return 0;
}

horizontalzoomout()
{
    while(ImageSize>0)
    {
        fread(buffer,1,bytesperpel,fp1);
	    fread(buffer,1,bytesperpel,fp1);            
	    fwrite(buffer,1,bytesperpel,fp2);
        readnum=readnum-(bytesperpel*2);
        writezoomoutnum=writezoomoutnum-bytesperpel;
        ImageSize=ImageSize-(bytesperpel*2);
	    count++;
        if(count==biWid/2)
	    {
            while(writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }
            if(ImageSize==0)
            {
                break;
            }
	        
            count=0;
            readnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
            writezoomoutnum=(int)(4*ceil((double)(biWid*bytesperpel)/8));
	    }
    }
    printf("EOF.....\n");
    return 0;
}

verticalzoomout()
{
    writezoomoutnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
    while(ImageSize>0)
    {
        fread(buffer,1,bytesperpel,fp1);
	    fwrite(buffer,1,bytesperpel,fp2);
        readnum=readnum-(bytesperpel);
        writezoomoutnum=writezoomoutnum-bytesperpel;
        ImageSize=ImageSize-(bytesperpel);
	    count++;
        if(count==biWid)
	    {
            while(writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }
            if(ImageSize==0)
            {
                break;
            }
	        
            fseek(fp1,actHoriSize,SEEK_CUR);//skip one row
            ImageSize=ImageSize-actHoriSize;
            
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
            writezoomoutnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
	    }
    }
    printf("EOF.....\n");
    return 0;
}

horizontalzoomin()
{
    while(ImageSize>0)
    {
        fread(buffer,1,bytesperpel,fp1);
	    fwrite(buffer,1,bytesperpel,fp2);
	    fwrite(buffer,1,bytesperpel,fp2);
        readnum=readnum-bytesperpel;
        writezoominnum=writezoominnum-(bytesperpel*2);
        ImageSize=ImageSize-bytesperpel;
        count++;
	    
	    if(count==biWid)
	    {
            tmpwritezoominnum=writezoominnum;
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
	        	        
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }
            if(ImageSize==0)
            {
                break;
            }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
            writezoominnum=(int)(4*ceil((double)(biWid*bytesperpel)/2));
	    }
    }
    printf("EOF.......\n");
                
    return 0;
}

verticalzoomin()
{
    tmpwritezoominnum=readnum;
    while(ImageSize>0)
    {
        fread(buffer,1,bytesperpel,fp1);
	    fwrite(buffer,1,bytesperpel,fp2);
	    readnum=readnum-bytesperpel;
        ImageSize=ImageSize-bytesperpel;
            
	    if(readnum==0)
	    {
            fseek(fp1,-(tmpwritezoominnum),SEEK_CUR);
            readnum=tmpwritezoominnum;
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                fwrite(buffer,1,1,fp2);
                readnum--;
            }
            
            if(ImageSize==0)
            {
                break;
            }
	        readnum=(int)(4*ceil((double)(biWid*bytesperpel)/4));
            writezoominnum=(int)(4*ceil((double)(biWid*bytesperpel)/2));
	    }
    }
    printf("EOF.......\n");
                
    return 0;
}

zoominbit()
{
    readnum=(int)(4*ceil((double)(biWid*1)/32));
    writezoominnum=(int)(4*ceil((double)(biWid*1)/16));
    tmpwritezoominnum=readnum;

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        temp=0;
        for(i=0;i<4;i++)
        {
            buffer1=buffer[0] & 0x80;
            if(buffer1 != 0)
            {
                temp=temp | 0x03;
            }
            else
            {
                temp=temp & 0xfc;
            }
            buffer[0]=buffer[0]<<1;
            if(i==3)
                break;
            temp=temp<<2;
        }
        buffer1=buffer[0];
        buffer[0]=temp;

	    fwrite(buffer,1,1,fp2);

        temp=0;
        buffer[0]=buffer1;
        for(i=0;i<4;i++)
        {
            buffer1=buffer[0] & 0x80;
            if(buffer1 != 0)
            {
                temp=temp | 0x03;
            }
            else
            {
                temp=temp & 0xfc;
            }
            buffer[0]=buffer[0]<<1;
            if(i==3)
                break;
            temp=temp<<2;
        }
        buffer[0]=temp;
	    fwrite(buffer,1,1,fp2);

        readnum=readnum-1;
        ImageSize=ImageSize-1;
        writezoominnum=writezoominnum-2;
	    count++;
	    
        if(count==biWid/8)
	    {
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }

            if(ImageSize==0)
            {
                break;
            }

            fseek(fp1,-(tmpwritezoominnum),SEEK_CUR);

	        while(tmpwritezoominnum>0)
            {
                fread(buffer,1,1,fp1);
	            temp=0;
                buffer1=0;
                for(i=0;i<4;i++)
                {
                    buffer1=buffer[0] & 0x80;
                    if(buffer1 != 0)
                    {
                        temp=temp | 0x03;
                    }
                    else
                    {
                        temp=temp & 0xfc;
                    }
                    buffer[0]=buffer[0]<<1;
                    if(i==3)
                        break;
                    temp=temp<<2;
                }
                buffer1=buffer[0];
                buffer[0]=temp;

	            fwrite(buffer,1,1,fp2);

                temp=0;
                buffer[0]=buffer1;
                for(i=0;i<4;i++)
                {
                    buffer1=buffer[0] & 0x80;
                    if(buffer1 != 0)
                    {
                        temp=temp | 0x03;
                    }
                    else
                    {
                        temp=temp & 0xfc;
                    }
                    buffer[0]=buffer[0]<<1;
                    if(i==3)
                        break;
                    temp=temp<<2;
                }
                buffer[0]=temp;
	            fwrite(buffer,1,1,fp2);

	            tmpwritezoominnum--;
	        }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*1)/32));
            writezoominnum=(int)(4*ceil((double)(biWid*1)/16));
            tmpwritezoominnum=readnum;
        }
    }
    printf("EOF......\n");
    return 0;
}

zoomoutbit()
{
    readnum=(int)(4*ceil((double)(biWid*1)/32));
    writezoomoutnum=(int)(4*ceil((double)(biWid*1)/64));

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        readnum=readnum-1;
        ImageSize=ImageSize-1;
					
		for(i=0;i<4;i++)
		{
			buffer1=buffer[0] & 0x80;
			if(buffer1 != 0)
			{
				temp=temp | 1;
			}
			else
			{
				temp=temp & 0xfe;
			}
			temp=temp<<1;
			buffer[0]=buffer[0]<<1;
			buffer[0]=buffer[0]<<1;
		}
		
	    fread(buffer,1,1,fp1);
        readnum=readnum-1;
        ImageSize=ImageSize-1;
			
		for(i=0;i<4;i++)
		{
			buffer1=buffer[0] & 0x80;
			if(buffer1 != 0)
			{
				temp=temp | 1;
			}
			else
			{
				temp=temp & 0xfe;
			}
            if(i==3)
                break;
			temp=temp<<1;
			buffer[0]=buffer[0]<<1;
			buffer[0]=buffer[0]<<1;
		}
        if(ImageSize==0)
        {
            return 0;
        }
					
        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);
        writezoomoutnum--;
        count++;
        if(count==biWid/16)
        {
            while (writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum--;
            }

            while (readnum>0)
            {
                fread(buffer,1,1,fp1);
                readnum--;
                ImageSize=ImageSize-1;
            }

            readnum=(int)(4*ceil((double)(biWid*1)/32));
            writezoomoutnum=(int)(4*ceil((double)(biWid*1)/64));
            fseek(fp1,readnum,SEEK_CUR);//skip one row
            ImageSize=ImageSize-readnum;
	        count=0;
        }
    }
    printf("EOF......\n");
    return 0;	        
}

horizontalzoominbit()
{
    readnum=(int)(4*ceil((double)(biWid*1)/32));
    writezoominnum=(int)(4*ceil((double)(biWid*1)/16));
    tmpwritezoominnum=readnum;

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        readnum=readnum-1;
        temp=0;
        for(i=0;i<4;i++)
        {
            buffer1=buffer[0] & 0x80;
            if(buffer1 != 0)
            {
                temp=temp | 0x03;
            }
            else
            {
                temp=temp & 0xfc;
            }
            buffer[0]=buffer[0]<<1;
            if(i==3)
                break;
            temp=temp<<2;
        }
        buffer1=buffer[0];
        buffer[0]=temp;

	    fwrite(buffer,1,1,fp2);
        writezoominnum=writezoominnum-1;

        temp=0;
        buffer[0]=buffer1;
        for(i=0;i<4;i++)
        {
            buffer1=buffer[0] & 0x80;
            if(buffer1 != 0)
            {
                temp=temp | 0x03;
            }
            else
            {
                temp=temp & 0xfc;
            }
            buffer[0]=buffer[0]<<1;
            if(i==3)
                break;
            temp=temp<<2;
        }
        buffer[0]=temp;
	    fwrite(buffer,1,1,fp2);
        writezoominnum=writezoominnum-1;
        ImageSize=ImageSize-1;
        
	    count++;
        if(count==biWid/8)
	    {
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }

            if(ImageSize==0)
            {
                break;
            }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*1)/32));
            writezoominnum=(int)(4*ceil((double)(biWid*1)/16));
            tmpwritezoominnum=readnum;
        }
    }
    printf("EOF......\n");
    return 0;
}

horizontalzoomoutbit()
{
    readnum=(int)(4*ceil((double)(biWid*1)/32));
    writezoomoutnum=(int)(4*ceil((double)(biWid*1)/64));

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        readnum=readnum-1;
        ImageSize=ImageSize-1;
					
		for(i=0;i<4;i++)
		{
			buffer1=buffer[0] & 0x80;
			if(buffer1 != 0)
			{
				temp=temp | 1;
			}
			else
			{
				temp=temp & 0xfe;
			}
			temp=temp<<1;
			buffer[0]=buffer[0]<<1;
			buffer[0]=buffer[0]<<1;
		}
		
	    fread(buffer,1,1,fp1);
        readnum=readnum-1;
        ImageSize=ImageSize-1;
			
		for(i=0;i<4;i++)
		{
			buffer1=buffer[0] & 0x80;
			if(buffer1 != 0)
			{
				temp=temp | 1;
			}
			else
			{
				temp=temp & 0xfe;
			}
            if(i==3)
                break;
			temp=temp<<1;
			buffer[0]=buffer[0]<<1;
			buffer[0]=buffer[0]<<1;
		}
        if(ImageSize==0)
        {
            break;
        }
					
        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);
        writezoomoutnum=writezoomoutnum-1;
        count++;
        if(count==biWid/16)
        {
            while (writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum=writezoomoutnum-1;
            }

            while (readnum>0)
            {
                fread(buffer,1,1,fp1);
                readnum--;
                ImageSize=ImageSize-1;
            }

            readnum=(int)(4*ceil((double)(biWid*1)/32));
            writezoomoutnum=(int)(4*ceil((double)(biWid*1)/64));
            if(ImageSize==0)
                break;
            count=0;
        }
    }
    printf("EOF......\n");
    return 0;
}

verticalzoominbit()
{
    readnum=(int)(4*ceil((double)(biWid*1)/32));
    writezoominnum=(int)(4*ceil((double)(biWid*1)/32));
    tmpwritezoominnum=readnum;

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
	    fwrite(buffer,1,1,fp2);

        readnum=readnum-1;
        ImageSize=ImageSize-1;
        writezoominnum=writezoominnum-1;
	    count++;
	    
        if(count==biWid/8)
	    {
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }

            if(ImageSize==0)
            {
                break;
            }

            fseek(fp1,-(tmpwritezoominnum),SEEK_CUR);
	        while(tmpwritezoominnum>0)
            {
                fread(buffer,1,1,fp1);
	            fwrite(buffer,1,1,fp2);
	            tmpwritezoominnum=tmpwritezoominnum-1;
	        }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*1)/32));
            writezoominnum=(int)(4*ceil((double)(biWid*1)/32));
            tmpwritezoominnum=readnum;
        }
    }
    printf("EOF......\n");
    return 0;
}

verticalzoomoutbit()
{
    readnum=(int)(4*ceil((double)(biWid*1)/32));
    writezoomoutnum=(int)(4*ceil((double)(biWid*1)/32));

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        fwrite(buffer,1,1,fp2);
        writezoomoutnum=writezoomoutnum-1;
        ImageSize=ImageSize-1;
        readnum=readnum-1;
        
        count++;
        if(count==biWid/8)
        {
            while (writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum=writezoomoutnum-1;
            }

            while (readnum>0)
            {
                fread(buffer,1,1,fp1);
                readnum--;
                ImageSize=ImageSize-1;
            }

            if(ImageSize==0)
                break;

            readnum=(int)(4*ceil((double)(biWid*1)/32));
            writezoomoutnum=(int)(4*ceil((double)(biWid*1)/32));
            fseek(fp1,readnum,SEEK_CUR);//skip one row
            ImageSize=ImageSize-readnum;
	        count=0;
        }
    }
    printf("EOF......\n");
    return 0;	        
}

zoominbit4()
{
    readnum=(int)(4*ceil((double)(biWid*4)/32));
    writezoominnum=(int)(4*ceil((double)(biWid*4)/16));
    tmpwritezoominnum=writezoominnum;

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        temp=0;
        buffer1=buffer[0] & 0xf0;
        temp=temp | buffer1;
        buffer1=buffer1>>4;
        buffer1=buffer1 & 0x0f;
        temp=temp | buffer1;
        
        buffer1=buffer[0];
        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);
        writezoominnum=writezoominnum-1;
        
        temp=0;
        buffer[0]=buffer1;
        buffer1=0;
        buffer1=buffer[0] & 0x0f;
        temp=temp | buffer1;
        buffer1=buffer1<<4;
        buffer1=buffer1 & 0xf0;
        temp=temp | buffer1;

        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);
        
        readnum=readnum-1;
        ImageSize=ImageSize-1;
        writezoominnum=writezoominnum-1;
	    count++;
	    
        if(count==biWid/8)
	    {
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }

            if(ImageSize==0)
            {
                break;
            }

            fseek(fp1,-(tmpwritezoominnum),SEEK_CUR);

	        while(tmpwritezoominnum>0)
            {
                fread(buffer,1,1,fp1);
                temp=0;
                buffer1=buffer[0] & 0xf0;
                temp=temp | buffer1;
                buffer1=buffer1>>4;
                buffer1=buffer1 & 0x0f;
                temp=temp | buffer1;
        
                buffer1=buffer[0];
                buffer[0]=temp;
                fwrite(buffer,1,1,fp2);
                tmpwritezoominnum=tmpwritezoominnum-1;
        
                temp=0;
                buffer[0]=buffer1;
                buffer1=0;
                buffer1=buffer[0] & 0x0f;
                temp=temp | buffer1;
                buffer1=buffer1<<4;
                buffer1=buffer1 & 0xf0;
                temp=temp | buffer1;

                buffer[0]=temp;
                fwrite(buffer,1,1,fp2);
        
                tmpwritezoominnum=tmpwritezoominnum-1;
	        }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*4)/32));
            writezoominnum=(int)(4*ceil((double)(biWid*4)/16));
            tmpwritezoominnum=writezoominnum;
        }
    }
    printf("EOF......\n");
    return 0;
}

zoomoutbit4()
{
    readnum=(int)(4*ceil((double)(biWid*4)/32));
    writezoomoutnum=(int)(4*ceil((double)(biWid*4)/64));

    while(ImageSize>0)
    {
        temp=0;
        fread(buffer,1,1,fp1);
        temp=buffer[0] & 0xf0;
        
        fread(buffer,1,1,fp1);
        buffer[0]=buffer[0]>>4;
        buffer[0]=buffer[0] & 0x0f;
        temp=temp | buffer[0];
        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);

        readnum=readnum-2;
        ImageSize=ImageSize-2;
        writezoomoutnum=writezoomoutnum-1;
					
		if(ImageSize==0)
        {
            return 0;
        }
		count++;
        
        if(count==biWid/16)
        {
            while (writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum--;
            }

            while (readnum>0)
            {
                fread(buffer,1,1,fp1);
                readnum--;
                ImageSize=ImageSize-1;
            }

            readnum=(int)(4*ceil((double)(biWid*4)/32));
            writezoomoutnum=(int)(4*ceil((double)(biWid*4)/64));
            fseek(fp1,readnum,SEEK_CUR);//skip one row
            ImageSize=ImageSize-readnum;
	        count=0;
        }
    }
    printf("EOF......\n");
    return 0;
}

verticalzoominbit4()
{
    readnum=(int)(4*ceil((double)(biWid*4)/32));
    writezoominnum=(int)(4*ceil((double)(biWid*4)/32));
    tmpwritezoominnum=readnum;

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
	    fwrite(buffer,1,1,fp2);

        readnum=readnum-1;
        ImageSize=ImageSize-1;
        writezoominnum=writezoominnum-1;
	    count++;
	    
        if(count==biWid/8)
	    {
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }

            if(ImageSize==0)
            {
                break;
            }

            fseek(fp1,-(tmpwritezoominnum),SEEK_CUR);
	        while(tmpwritezoominnum>0)
            {
                fread(buffer,1,1,fp1);
	            fwrite(buffer,1,1,fp2);
	            tmpwritezoominnum=tmpwritezoominnum-1;
	        }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*4)/32));
            writezoominnum=(int)(4*ceil((double)(biWid*4)/32));
            tmpwritezoominnum=readnum;
        }
    }
    printf("EOF......\n");
    return 0;
}

verticalzoomoutbit4()
{
    readnum=(int)(4*ceil((double)(biWid*4)/32));
    writezoomoutnum=(int)(4*ceil((double)(biWid*4)/32));

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        fwrite(buffer,1,1,fp2);
        writezoomoutnum=writezoomoutnum-1;
        ImageSize=ImageSize-1;
        readnum=readnum-1;
        
        count++;
        if(count==biWid/8)
        {
            while (writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum=writezoomoutnum-1;
            }

            while (readnum>0)
            {
                fread(buffer,1,1,fp1);
                readnum--;
                ImageSize=ImageSize-1;
            }

            if(ImageSize==0)
                break;

            readnum=(int)(4*ceil((double)(biWid*4)/32));
            writezoomoutnum=(int)(4*ceil((double)(biWid*4)/32));
            fseek(fp1,readnum,SEEK_CUR);//skip one row
            ImageSize=ImageSize-readnum;
	        count=0;
        }
    }
    printf("EOF......\n");
    return 0;
}

horizontalzoominbit4()
{
    readnum=(int)(4*ceil((double)(biWid*4)/32));
    writezoominnum=(int)(4*ceil((double)(biWid*4)/16));
    tmpwritezoominnum=readnum;

    while(ImageSize>0)
    {
        fread(buffer,1,1,fp1);
        temp=0;
        buffer1=buffer[0] & 0xf0;
        temp=temp | buffer1;
        buffer1=buffer1>>4;
        buffer1=buffer1 & 0x0f;
        temp=temp | buffer1;
        
        buffer1=buffer[0];
        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);
        writezoominnum=writezoominnum-1;
        
        temp=0;
        buffer[0]=buffer1;
        buffer1=0;
        buffer1=buffer[0] & 0x0f;
        temp=temp | buffer1;
        buffer1=buffer1<<4;
        buffer1=buffer1 & 0xf0;
        temp=temp | buffer1;

        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);
        writezoominnum=writezoominnum-1;
        ImageSize=ImageSize-1;
        readnum=readnum-1;
        
	    count++;
        if(count==biWid/8)
	    {
            while(writezoominnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoominnum--;
            }
            while(readnum>0)
            {
                fread(buffer,1,1,fp1);
                ImageSize=ImageSize-1;
                readnum--;
            }
            if(ImageSize==0)
            {
                break;
            }
	        count=0;
            readnum=(int)(4*ceil((double)(biWid*4)/32));
            writezoominnum=(int)(4*ceil((double)(biWid*4)/16));
            tmpwritezoominnum=readnum;
        }
    }
    printf("EOF......\n");
    return 0;
}

horizontalzoomoutbit4()
{
    readnum=(int)(4*ceil((double)(biWid*4)/32));
    writezoomoutnum=(int)(4*ceil((double)(biWid*4)/64));

    while(ImageSize>0)
    {
        temp=0;
        fread(buffer,1,1,fp1);
        temp=buffer[0] & 0xf0;
        
        fread(buffer,1,1,fp1);
        buffer[0]=buffer[0]>>4;
        buffer[0]=buffer[0] & 0x0f;
        temp=temp | buffer[0];
        buffer[0]=temp;
        fwrite(buffer,1,1,fp2);

        readnum=readnum-2;
        ImageSize=ImageSize-2;
        writezoomoutnum=writezoomoutnum-1;

        if(ImageSize==0)
        {
            break;
        }
		       
        count++;
        if(count==biWid/16)
        {
            while (writezoomoutnum>0)
            {
                buffer[0]=0;
                fwrite(buffer,1,1,fp2);
                writezoomoutnum=writezoomoutnum-1;
            }

            while (readnum>0)
            {
                fread(buffer,1,1,fp1);
                readnum--;
                ImageSize=ImageSize-1;
            }

            readnum=(int)(4*ceil((double)(biWid*4)/32));
            writezoomoutnum=(int)(4*ceil((double)(biWid*4)/64));
            if(ImageSize==0)
                break;
            count=0;
        }
    }
    printf("EOF......\n");
    return 0;	   
}