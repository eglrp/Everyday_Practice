% clear all
% clc;
% B=imread('C:\Users\ranji\Desktop\test.bmp');
% A=rgb2gray(B);
% A2=dct2(A);
% A3=fft2(A);
% subplot(2,2,1);imshow(B);
% subplot(2,2,2);imshow(A);
% subplot(2,2,3);imshow(A2);
% subplot(2,2,4);imshow(A3);
% %tab��������ʾ

% function test=subim(f,m,n,rx,ry)
% test=zeros(m,n);
% rowhigh=rx+m-1;
% colhigh=ry+n-1;
% xcount=0;
% for r=rx:rowhigh
%     xcount=xcount+1;
%     ycount=0;
%     for c=ry:colhigh
%         ycount=ycount+1;
%         test(xcount,ycount)=f(r,c);
%     end
% end

%�����任
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% g=imadjust(A,[0 1],[1 0]);
% gs=im2uint8(mat2gray(A));
% gg=im2uint8(mat2gray(log(1+double(A))));
% %imshow(A),figure,imshow(g),figure,imshow(gs)
% subplot(2,2,1);imshow(A)
% subplot(2,2,2);imshow(g)
% subplot(2,2,3);imshow(gs)
% subplot(2,2,4);imshow(gg);

%%����intrans.m�����и��ֿռ�任Ч��

%ֱ��ͼ
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% h=imhist(B);
% h1=h(1:10:256);
% horz=1:10:256;
% %bar(horz,h1);
% %stem(horz,h1,'fill');
% plot(h);
% axis([0 255 0 1500]);
% set(gca,'xtick',0:50:255);
% set(gca,'ytick',0:200:1500);

%%ֱ��ͼ���⻯
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% figure , imhist(B);
% ylim('auto')
% g=histeq(B,256);
% figure,imshow(g)
% figure,imhist(g)
% ylim('auto')
% %imwrite(g,'save.bmp'); 
% 
% hnorm=imhist(B)./numel(B);
% cdf=cumsum(hnorm);
% x=linspace(0,1,256);
% plot(x,cdf);
% axis([0 1 0 1]);
% set(gca,'xtick',0:.2:1);
% set(gca,'ytick',0:.2:1);
% xlabel('Input intensity values','fontsize',9);
% ylabel('Output intensity values','fontsize',9);
% text(0.18,0.5,'Transformation function','fontsize',9);

%%ֱ��ͼƥ��,����˹������manualhist.m�ļ�

% %%���Կռ��˲�
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B1=A(:,:,1);
% imshow(B1);
% B=B1(10:180,50:220);
% B=double(B); %��ת�����ǿհ׵�
% w=ones(17);
% gd=imfilter(B,w);
% figure, imshow(gd,[ ]);  %ģ��Ч������
% 
% gr=imfilter(B,w,'replicate');  %���˲�����ͼ����о�����������ģ��Ч��
% figure, imshow(gr,[]); 
% 
% gs=imfilter(B,w,'symmetric');
% figure, imshow(gs,[]);
% 
% gc=imfilter(B,w,'circular');
% figure,imshow(gc,[]);
% 
% C=im2double(B);
% gDr=imfilter(C,w,'replicate');
% figure, imshow(gDr,[]);

%�����Կռ��˲� colfilt.m�ļ�

% %%��׼�ռ��˲���
% %%���Կռ��˲�
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% w=fspecial('laplacian',0);
% w1=[1,1,1;1,-8,1;1,1,1];  %�ֹ�ָ���˲���
% g1=imfilter(B,w,'replicate');
% figure, imshow(g1,[]);
% B1=im2double(B);
% g2=imfilter(B1,w,'replicate');
% g3=imfilter(B1,w1,'replicate');
% figure ,imshow(g2,[])  %Ĭ������ʾ0~255,����[]����ʾmin(A)~max(A),imshow(A,[])������С�����������ʾ
% figure ,imshow(g3,[]);
% g=B1-g2;
% gg=B1-g3;
% figure,imshow(g); %��Ч����,��laplas��ǿͼ��
% figure,imshow(gg);title('w1�˲���');%ͼ������  

% %%�����Կռ��˲�
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.2);
% gm=medfilt2(fn);  %��ֵ�˲�ȥ��
% figure,imshow(gm);
% gms=medfilt2(fn,'symmetric'); %symmetric
% figure, imshow(gms);











