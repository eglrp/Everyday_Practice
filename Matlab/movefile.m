
% %%%%%%%%%%%%%%�����޸��ļ���һ���ļ���   \·����ֱ��Ϊ�ļ�
% close all;clear all;clc;
% path='G:\100�����\YC_AK����\value-100\version-15\direction-1\�½��ļ���\';
% fileDIR=dir(strcat(path,'*.txt'));  %��ȡ·����Ϣ    %��0���ļ���direction
% filenum=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ
% cd(path);
% for i=0:2:filenum-1
%     name1=fileDIR(i+1).name;
%     name2=fileDIR(i+2).name;
%     movefile(name1,strcat(num2str(i/2),'_down.bmp'));
%     movefile(name2,strcat(num2str(i/2),'_up.bmp'));
% end

%%%%%%%%%%%%%%�����޸��ļ��������ļ���   \·�����ļ���\�ļ�
close all;clear all;clc;
path='G:\48_7_20161023\2015��\AK47DL\value-100\';
fileDIR1=dir(strcat(path,'*')); %��һ���ļ���direction-
filenum1=length(fileDIR1);
for q=3:filenum1
    filename1=fileDIR1(q).name;
    path2=strcat(path,filename1,'\');
    DIR=dir(strcat(path2,'*.bmp')); %��ȡ�����ļ���������bmp��ʽ��ͼ��,��0��ʼ
    len=length(DIR);
    
    cd(path2);
    if len>0
        for i=0:2:len-1
            if ((i+2)<=len & (i+1)<=len)
                name1=DIR(i+1).name;
                name2=DIR(i+2).name;
                movefile(name1,strcat(num2str(i/2),'_down.bmp'));
                movefile(name2,strcat(num2str(i/2),'_up.bmp'));
            end
        end
    end
    %  end
end

% close all;clear all;clc;
% path='G:\100�����\YC_AK����\value-10\direction-0\1\';
% fileDIR=dir(strcat(path,'*.bmp'));  %��ȡ·����Ϣ    %��0���ļ���direction
% len=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ
% cd(path);
% if len>0
%     for i=1:len/2
%         oldname=strcat('Image_Y_all',num2str(i-1),'.bmp');
%         newname=strcat(num2str(i-1),'_up.bmp');
%         movefile(oldname,newname);
%         oldname=strcat('Image_U_all',num2str(i-1),'.bmp');
%         newname=strcat(num2str(i-1),'_down.bmp');
%         movefile(oldname,newname);
%     end
% end



% %%%%%%%%%%%%%%�����޸��ļ��������ļ���   \·�����ļ���\�ļ���\�ļ�
% close all;clear all;clc;
% path='G:\100�����\5Ԫ����20000��\';
% fileDIR=dir(path);  %��ȡ·����Ϣ    %��0���ļ���direction
% filenum=length(fileDIR);   %���ļ����µ����ļ��и�������3��ʼ
% for p=5:filenum  %
%     filename=fileDIR(p).name;  %��p�����ļ��е��ļ�����
%     path1=strcat(path,filename,'\');
%     fileDIR1=dir(strcat(path1,'*')); %��һ���ļ���1-50
%     filenum1=length(fileDIR1);
%     for q=3:filenum1
%         filename1=fileDIR1(q).name;
%         path2=strcat(path1,filename1,'\');
%         DIR=dir(strcat(path2,'*.bmp')); %��ȡ�����ļ���������bmp��ʽ��ͼ��,��0��ʼ
%         len=length(DIR);
%         
%         cd(path2);
%         if len>0
%             for i=0:2:len-1
%                 if ((i+2)<=len & (i+1)<=len)
%                     name1=DIR(i+1).name;
%                     name2=DIR(i+2).name;
%                     movefile(name1,strcat(num2str(i/2),'_down.bmp'));
%                     movefile(name2,strcat(num2str(i/2),'_up.bmp'));
%                 end
%             end
%         end
%     end
% end