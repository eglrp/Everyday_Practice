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
% w=fspecial('laplacian',0);  %generate �˲���ģ
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

% %%���㲢���ӻ���άDFT
% A=imread(' C:\Users\ranji\Desktop\test.jpg');  %����ʹ��save.bmpʵ��
% B=A(:,:,1);
% B=B(50:700,150:950);
% imshow(B);
% F=fft2(B);
% S=abs(F);
% figure,imshow(S,[]);% �׵������Ͻ�
% Fc=fftshift(F);
% figure, imshow(abs(Fc),[]); %�׵������ĵ�
% S2=log(1+abs(Fc));
% figure,imshow(S2,[]);

% %%eg4.1���������˲�
% close all;
% clear all;
% clc;
% A=imread(' C:\Users\ranji\Desktop\test.jpg');  %����ʹ��save.bmpʵ��
% B=A(:,:,1);
% B=B(50:700,150:950);
% imshow(B);
% [M,N]=size(B);
% F=fft2(B);
% sig=10;
% H=lpfilter('gaussian',M,N,sig);
% G=H.*F;
% g=real(ifft2(G));
% figure,imshow(g,[]);   %ͼ��ģ��
% 
% %%ʹ���������˲� Ƶ���˲��Ļ������裺
% PQ=paddedsize(size(B));
% Fp=fft2(B,PQ(1),PQ(2)); %Compute the FFT with padding
% Hp=lpfilter('gaussian',PQ(1),PQ(2),2*sig);
% Gp=Hp.*Fp;  %Ƶ���������
% gp=real(ifft2(Gp));
% gpc=gp(1:size(B,1),1:size(B,2));
% figure, imshow(gpc,[]);
% %�ռ��˲�Ч��
% h=fspecial('gaussian',15,7);
% gs=imfilter(B,h);
% figure,imshow(gs);


% %%4.4�ռ��˲�����Ƶ���˲����ıȽ�
% close all;
% clear all;
% clc;
% A=imread(' C:\Users\ranji\Desktop\test.jpg');  %����ʹ��save.bmpʵ��
% B=A(:,:,1);
% B=B(101:700,151:750);
% imshow(B);
% imwrite(B,'test1.bmp');
% F=fft2(B);
% ss=abs(F);%����ÿһ��Ԫ�صķ���
% S=fftshift(log(1+abs(F)));
% S=gscale(S);
% figure,imshow(S);
% h=fspecial('sobel')';
% figure,freqz2(h);
% PQ=paddedsize(size(B));
% figure,freqz2(h,PQ(1),PQ(2));
% H=freqz2(h,PQ(1),PQ(2));
% H1=ifftshift(H);
% figure,imshow(abs(H),[]);
% figure,imshow(abs(H1),[]);
% 
% %�ռ����Ƶ����
% gs=imfilter(double(B),h);
% gf=dftfilt(B,H1);
% figure,imshow(gs,[]); %�и�ֵ
% figure,imshow(gf,[]);
% figure,imshow(abs(gs),[]);
% figure,imshow(abs(gf),[]);
% %������ֵ��ֵͼ��
% figure,imshow(abs(gs)>0.2*abs(max(gs(:))));
% figure,imshow(abs(gf)>0.2*abs(max(gf(:))));

% %%4.5��Ƶ����ֱ�������˲���
% A=imread(' C:\Users\ranji\Desktop\test1.bmp');  
% imshow(A);
% PQ=paddedsize(size(A)); %ִ��ʱҪ����Ӧ����Ŀ¼�ļ�
% [U,V]=dftuv(PQ(1),PQ(2));
% D0=0.05*PQ(2);
% F=fft2(A,PQ(1),PQ(2));
% H=exp(-(U.^2+V.^2)/(2*(D0^2)));  %��˹��ͨ�˲���
% g=dftfilt(A,H);
% figure,imshow(fftshift(H),[]); %��ͼ�����ʽ��ʾ�ĸ�˹��ͨ�˲���
% figure,imshow(log(1+abs(fftshift(F))),[]);
% figure,imshow(g,[]); %ͼ���ģ��

% %�߿�ͼ�ͱ���ͼ
% H=fftshift(lpfilter('gaussian',500,500,50));
% mesh(H(1:10:500,1:10:500));
% axis([0 50 0 50 0 1]);
% colormap([0 0 0]);
% axis off
% grid off
% view(-25,30)
% %view(-25,0)
% surf(H)
% colormap(gray)

%[Y,X]=meshgrid(-2:0.1:2,-2:0.1:2);
%Z=X.*exp(-X.^2+Y.^2);
%mesh(Z)
%surf(Z)
%meshgrid(Z);

%%��ͨ�˲�����ǿ
% close all
% clc;
% H=fftshift(hpfilter('ideal',500,500,50));
% mesh(H(1:10:500,1:10:500)); %�߿�ͼ
% %surf(H); %����ͼ
% axis([0 50 0 50 0 1]);
% colormap([0 0 0]); 
% axis off 
% grid off
% figure,imshow(H,[]);
% A=imread(' C:\Users\ranji\Desktop\test1.bmp');
% PQ=paddedsize(size(A));
% D0=0.05*PQ(1);
% H=hpfilter('gaussian',PQ(1),PQ(2),D0);
% g=dftfilt(A,H);
% figure,imshow(g,[])

% %%��Ƶǿ���˲�
% close all
% clear all
% clc;
% A=imread(' C:\Users\ranji\Desktop\test1.bmp');
% imshow(A);
% PQ=paddedsize(size(A));
% D0=0.05*PQ(1);
% HBW=hpfilter('btw',PQ(1),PQ(2),D0);
% H=0.5+2*HBW;
% gbw=dftfilt(A,HBW);
% figure,imshow(gbw);  %��[]������
% gbw=gscale(gbw);
% figure,imshow(gbw);
% ghf=dftfilt(A,H);
% figure,imshow(ghf,[])
% ghf=gscale(ghf);
% figure,imshow(ghf,[])
% ghe=histeq(ghf,256);
% figure,imshow(ghe,[]);

% %%������������
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.2);
% C=fn+B;
% figure,imshow(C);
% [b,c,r]=roipoly(C); %%�ȴ�ѡ������
% [p,npix]=histroi(C,c,r);
% figure,bar(p,1)
% 
% [v,unv]=statmoments(p,2)  %���������ֵ�ͷ��� 
% X=imnoise2('gaussian',npix,1,147,20);
% figure,hist(X,130);
% axis([0 300 ])


% %%����spfilt��==ʹ�ý��������ĸ�ԭ
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.2);
% C=fn+B;
% figure,imshow(C);
% %����������Ⱦ
% [M,N]=size(B);
% R=imnoise2('salt & pepper', M , N , 0.1 , 0);
% c=find(R==0);
% gp=B;
% gp(c)=0;
% figure,imshow(gp);
% %���˺�������,����QΪ��ֵ�ķ������˲���
% fp=spfilt(gp,'chmean',3,3,1.5);
% figure,imshow(fp);
% %max
% fpmax=spfilt(gp,'max',3,3);
% figure,imshow(fpmax)
% 
% %�ν�������Ⱦ
% R1=imnoise2('salt & pepper',M,N,0,0.1);
% c=find(R==1);
% gs=B;
% gs(c)=255;
% figure,imshow(gs);
% %�ν�������QΪ��ֵ�ķ������˲���
% fs=spfilt(gs,'chmean',3,3,-1.5);
% figure,imshow(fs);
% %min
% fsmin=spfilt(gs,'min',3,3);
% figure,imshow(fsmin);

% %%����Ӧ��ֵ�˲�
% close all
% clf;
% A=imread(' C:\Users\ranji\Desktop\test2.jpg');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.25);
% figure,imshow(fn);
% f1=medfilt2(fn,[7 7],'symmetric'); %û�����������Ǳ��ģ����ʧ��,�о�Ч��������
% figure,imshow(f1);
% f2=adpmedian(fn,7); %����Ӧ��ֵ�˲�
% figure,imshow(f2);

% %%%%%ģ������ͼ�񣬼��˻���ģ
% close all
% f=checkerboard(8); %���ɲ���ͼ��
% imshow(pixeldup(f,8),[]);  
% title('ԭͼ�Ŵ�')
% PSF=fspecial('motion',7,45);
% gb=imfilter(f,PSF,'circular');
% figure,imshow(pixeldup(gb,8),[]);
% title('ԭͼ���˻�����ģ��')
% noise=imnoise(zeros(size(f)),'gaussian',0,0.001);
% figure,imshow(pixeldup(noise,8),[]);
% title('����')
% g1=gb+noise;
% figure,imshow(pixeldup(g1,8),[]); 
% title('ԭͼ+�˻�ģ��+����');  %%���渴ԭ��ͼ
% 
% g=im2uint8(g);
% %%%%ά���˲� %Ҫ����ǰ����˻�ģ��
% fr1=deconvwnr(g,PSF);
% figure,imshow(pixeldup(fr1,8),[]);
% title('��ʽһ��ֱ�����˲��Ľ��');
% %�������R
% Sn=abs(fft2(noise)).^2; %noise power spectrum
% nA=sum(Sn(:))/prod(size(noise));  %prod.m  ���ھ��󷵻ص��ǰ�������������Ԫ�صĻ���Ȼ�����һ��������
% Sf=abs(fft2(f)).^2;
% fA=sum(Sf(:))/prod(size(f));
% R=nA/fA;
% fr2=deconvwnr(g,PSF,R);
% figure,imshow(pixeldup(fr2,8),[]);
% title('��ʽ�������ű���֪');  %Ч������
% %ʹ������غ���
% NCORR=fftshift(real(ifft2((Sn))));
% ICORR=fftshift(real(ifft2((Sf))));
% fr3=deconvwnr(g,PSF,NCORR,ICORR);
% figure,imshow(pixeldup(fr3,8),[]);
% title('��ʽ������������غ���');

% %%�ռ�任
% close all;
% T1=[3 0 0;0 2 0;0 0 1];
% tform1=maketform('affine',T1);
% vistformfwd(tform1,[0 100],[0 100]);
% title('ˮƽ��������3����ֱ��������2')
% 
% T2=[1 0 0;.2 1 0;0 0 1];
% tform2=maketform('affine',T2);
% figure,vistformfwd(tform2,[0 100],[0 100]);
% 
% Tscale=[1.5 0 0;0 2 0;0 0 1];
% Trotation=[cos(pi/4) sin(pi/4) 0
%     -sin(pi/4) cos(pi/4) 0
%     0 0 1];
% Tshear=[1 0 0;.2 1 0;0 0 1];
% T3=Tscale*Trotation*Tshear;
% tform3=maketform('affine',T3);
% figure,vistformfwd(tform3,[0 100],[0 100]);

% %%��ͼ��Ӧ�ÿռ�任--���ԵȽǱ任
% close all
% f=checkerboard(40);  %%����Ϊ8ʱ�������ͼ���ģ��;ò��Խ��Խ����
% imshow(pixeldup(f,8),[]);  
% s=0.8;
% theta=pi/6;
% T=[s*cos(theta) ,s*sin(theta) ,0;
%     -s*sin(theta) ,s*cos(theta), 0;
%     0, 0 ,1];
% tform=maketform('affine',T);
% g=imtransform(f,tform);
% figure,imshow(pixeldup(g,8),[]);  
% 
% g2=imtransform(f,tform,'nearest');
% figure,imshow(pixeldup(g2,8),[]); 


% %%RGBͼ��
% close all
% test2=imread('C:\Users\ranji\Desktop\test2.jpg');
% fR=test2(:,:,1);
% fG=test2(:,:,2);
% fB=test2(:,:,3);
% r=fR(1:8:end,1:8:end);
% g=fG(1:8:end,1:8:end);
% b=fB(1:8:end,1:8:end);
% imshow(r);
% figure,imshow(g);
% figure,imshow(b);
% rgb_image=cat(3,r,g,b);
% figure,imshow(rgb_image);
% %imwrite(rgb_image,'C:\Users\ranji\Desktop\rgb_image.jpg');

% %%����ͼ��
% close all
% clear all
% clc;
% rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% f=rgb2gray(rgb_image);
% [X,map]=gray2ind(f,100);
% imshow(X,map);
% % fd=mat2gray(f);
% %XX=grayslice(fd,0.89); %%ȫ�Ǻ�ɫ�ģ���
% [X1,map1]=rgb2ind(rgb_image,8,'nodither'); %RGBͼ�񴴽�����ͼ��
% figure,imshow(X1,map1);
% [X2,map2]=rgb2ind(rgb_image,8,'dither');
% figure,imshow(X2,map2);
% g=dither(f);
% figure,imshow(g),   %����Ч��


%%%svd�ع�ͼ��
% clear all;
% close all;
% clc;
% 
% a=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% 
% imshow(mat2gray(a))
% [m n]=size(a);
% a=double(a);
% %r=rank(a);
% [s v d]=svd(a(:,:,1));
% 
% %re=s*v*d';
% re=s(:,:)*v(:,1:1)*d(:,1:1)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\1.jpg')
% 
% re1=s(:,:)*v(:,1:20)*d(:,1:20)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\2.jpg')
% 
% re=s(:,:)*v(:,1:80)*d(:,1:80)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\3.jpg')
% 
% re=s(:,:)*v(:,1:150)*d(:,1:150)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\4.jpg')

% %% ����figure�ϱ�����ӱ���
% close all;
% for i=1:10
%     figure(i);
%     x = -pi:.1:pi;
%     y = sin(x); 
%     plot(x,y);
%     set(gca,'XTick',-pi:pi/2:pi);
%     set(gca,'XTickLabel',{'-pi','-pi/2','0','pi/2','pi'});
%     xlabel('-/pi /leq /Theta /leq /pi');    %ͼ���·�-1.22������x����������
%     ylabel('sin(/Theta)');                      %ͼ��y����������
%     a=[1,2,3,4,5,6,7,8,9,10];
%     % title('Plot of sin(/Theta)');      %ͼ���Ϸ������ַ������⣨string��
%     %title(['order=',num2str(i)]);    %ͼ���Ϸ�����������⣨variable��
%     title({'x in this figure is equal to' i});
%     %title(['order=',num2str(a(i))],'position',[0 -1.28]);    %ͼ���·��м����������⣨variable��
%     % title(['order=',num2str(a(2))],'position',[0 -1.22]);    %ͼ���·��м���'xlabel'ͬλ�ü���������⣨variable��
%     text(-pi/4,sin(-pi/4),'/leftarrow sin(-/pi/div4)',...
%         'HorizontalAlignment','left');                                      %ͼ��ע�ͣ�annotation��
%end

% %%��ɫͼ��ռ�ת��
% close all
% clear all
% clc;
% rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% yiq_image=rgb2ntsc(rgb_image); %RGBתYIQͼ��
% imshow(yiq_image);
% ycbcr_image=rgb2ycbcr(rgb_image);%RGBתYCBCR
% figure,imshow(ycbcr_image);
% hsv_image=rgb2hsv(rgb_image);% RGBתHSV
% figure,imshow(hsv_image);
% cmy_image=imcomplement(rgb_image); %RGBתHSI
% figure,imshow(cmy_image);
% hsi_imge=rgb2hsi(rgb_image); %RGBתHSI
% figure,imshow(hsi_imge);  %Ч����hsv�е���
% % ��ͬ������Ч��;
% hsi_h_image=hsi_imge(:,:,1);
% figure,imshow(hsi_h_image);
% hsi_s_image=hsi_imge(:,:,2);
% figure,imshow(hsi_s_image);
% hsi_i_image=hsi_imge(:,:,3);
% figure,imshow(hsi_i_image);


% %%��ɫͼ��ռ��˲�
% close all
% clear all
% clc;
% rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% imshow(rgb_image);
% %g=ice('image',rgb_image);
% lapmask=[1 1 1;1 -8 1; 1 1 1];
% fen=imsubtract(rgb_image,imfilter(rgb_image,lapmask,'replicate'));  %��ɫͼ����
% figure,imshow(fen);
% [VG,A,PPG]=colorgrad(rgb_image);%�ݶȵĲ�ɫ��Ե���
% figure,imshow(A);
% figure,imshow(VG);

%%��ɫͼ��ͼ��ָ�
close all
clear all
clc;
rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
mask=roipoly(rgb_image);  %select region interactively
red=immultiply(mask,rgb_image(:,:,1));
green=immultiply(mask,rgb_image(:,:,2));
blue=immultiply(mask,rgb_image(:,:,3));
g=cat(3,red,green,blue);
figure,imshow(g)

[M,N,K]=size(g);
I=reshape(g,M*N,3);
idx=find(mask);
I=double(I(idx,1:3));
[C,m]=covmatrix(I);
d=diag(C);
sd=sqrt(d)';
E25=colorseg('euclidean',rgb_image,50,m);  %Ч����̫�ã�����sd��ֵѡ����ֵ
figure,imshow(E25);
