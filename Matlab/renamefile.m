%%%%%%%%%%%%%%�����޸��ļ�������
% close all;clear all;clc;
% path='G:\100�����\����CIS������\value-5\version-4\direction-0\'; %�޸�һ���ļ�������
% fileDIR=dir(path);  %��ȡ·����Ϣ    %��0���ļ���direction
% filenum=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ  
% for p=3:filenum
%     filename=fileDIR(p).name;  %��p�����ļ��е��ļ�����    
%     path1=strcat(path,filename,'\');
%     fileDIR1=dir(strcat(path1,'*')); %��һ���ļ���1-50
%     filenum1=length(fileDIR1); 
%     for q=3:filenum1
%         filename1=fileDIR1(q).name;
%         path2=strcat(path1,filename1,'\');
%     DIR=dir(strcat(path2,'*.bmp')); %��ȡ�����ļ���������bmp��ʽ��ͼ��
%     len=length(DIR);
%    
%   cd(path2);
%     if len>0
%         for i=0:2:len-1
%             name1=DIR(i+1).name;
%             name2=DIR(i+2).name;
%            movefile(name1,strcat(num2str(i/2),'_down.bmp'));
%            movefile(name2,strcat(num2str(i/2),'_up.bmp'));
%         end
%     end
%     end
% end

% clear all
% clc
% %folder_name=uigetdir;
% folder_name='G:\100�����\����CIS������\value-5\version-4\direction-0\';
% % �ֶ���Ҫ�޸����Ƶ��ļ��е���һ���ļ���
% folder=dir(folder_name);
% oldname=cell(length(folder)-2,1);
% for ii=3:length(folder)
%    oldname{ii-2}=folder(ii).name;
% end
% 
% % ��ȡ��Ҫ�޸��ļ��е�����
% newname=cell(length(oldname),1);
% for ii=1:length(oldname)
%    a=oldname{ii};
%    %newname{ii}=a(2:end);
%    % �µ��ļ������� 
%    movefile([folder_name '\' oldname{ii}],[folder_name '\' num2str(ii)])
%    % ����movefile���������޸�
% end


%�������ļ�������
clear all
clc
close all;
folder_name='G:\100�����\5Ԫ����20000��\';
fileDir=dir(folder_name); 
folderNum=length(fileDir); %��һ��Ŀ¼ direction
for p=3:folderNum
    fileName=fileDir(p).name;
    path1=strcat(folder_name,fileName,'\');
    fileDIR1=dir(strcat(path1,'*'));
    
    for ii=3:length(fileDIR1)
        movefile([path1 '\' fileDIR1(ii).name],[path1 '\' num2str(ii-2)])
    end
end

