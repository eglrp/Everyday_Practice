
% %%%%%%%%%%%%%%һ��Ŀ¼��ɾ��raw�ļ�   \�ļ�
% close all;
% clear all;
% clc;
% path='G:\48_7_20161023\1999��\value-10\direction-0\';
% fileDIR=dir(strcat(path,'*.raw'));  %��ȡ·����Ϣ
% filenum=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ
% cd(path);
% if filenum>0
%     for i=1:filenum
%         rawname=fileDIR(i).name;
%         rawname=strcat(path,rawname);
%         delete(rawname);
%     end
% end

%%%%%%%%%%%%%%����Ŀ¼��ɾ��raw�ļ�    \�ļ���\�ļ�
close all;
clear all;
clc;
path='G:\48_7_20161023\2015��\AK47DL\value-100\';
fileDIR=dir(path);  %��ȡ·����Ϣ
filenum=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ
for p=3:filenum %
    filename=fileDIR(p).name;  %��p�����ļ��е��ļ�����
    path1=strcat(path,filename,'\');
    fileDIR1=dir(strcat(path1,'*.raw'));
    filenum1=length(fileDIR1);
    
    cd(path1);
    if filenum1>0
        for i=1:filenum1
            rawname=fileDIR1(i).name;
            rawname=strcat(path1,rawname);
            delete(rawname);
        end
    end
end

% %%%%%%%%%%%%%%����Ŀ¼��ɾ��raw�ļ�    \�ļ���\�ļ���\�ļ�
% close all;
% clear all;
% clc;
% path='E:\�г��Ŵ����\�г��Ŵ����\05-10\';
% fileDIR=dir(path);  %��ȡ·����Ϣ
% filenum=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ
% for p=3:filenum %
%     filename=fileDIR(p).name;  %��p�����ļ��е��ļ�����
%     path1=strcat(path,filename,'\');
%     fileDIR1=dir(strcat(path1,'*'));
%     filenum1=length(fileDIR1);
%     for q=3:filenum1
%         filename1=fileDIR1(q).name;
%         path2=strcat(path1,filename1,'\');
%     DIR=dir(strcat(path2,'*.raw')); %��ȡ�����ļ���������raw��ʽ��ͼ��
%     len=length(DIR);
%
%   cd(path2);
%     if len>0
%         for i=1:len
%             rawname=DIR(i).name;
%             rawname=strcat(path2,rawname);
%             delete(rawname);
%         end
%     end
%     end
% end
