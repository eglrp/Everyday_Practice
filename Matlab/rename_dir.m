function rename_dir(path, option)  
%Author:shizhixin  
%Email:szhixin@gmail.com  
%Blog:http://blog.csdn.net/shizhixin  
%Date:2012-02-15  
  
%option = 'LAMOST','DR8','SPECIAL'  
%LAMOST:����spec_release.php@path=%2Fdata1%2Fspectra_v2.3.3%2F20111024%  
% 2FF5902%2Fspec-55859-F5902_sp02-166.fits���ļ�����ֻȡ���沿��  
% ������Ϊspec-55859-F5902_sp02-166.fits  
%DR8: spec-pppp-mmmmm-ffff.fits  
%fits@plateid=278&mjd=51900&fiber=583���ļ�������Ϊspec-0278-51900-0583.fit  
%����λ����������  
%SPECIAL :Spec-2951-54592-433.fit  ---> spec-pppp-mmmmm-ffff.fits  
  
%EX:rename_dir('G:\DR8_data\', 'DR8')  
switch option  
    case 'LAMOST'  
        files = dir([path '*.fits']); %�����׺Ϊ.fits�������ļ�  
        n = length(files);           %�ļ�����  
        for i = 1:n  
            i  
            filename = [path files(i).name];    %�ļ���������·��  
            old_name = files(i).name;           %���������ļ���  
            pos = strfind(old_name, 'spec-');   %�ҵ�spec-��λ��  
            new_name = old_name(pos:end);       %��spec-��ʼֱ��������е��ַ�Ϊ�µ��ļ���  
            old_path = strcat(path,old_name);   %��ȡԭ���ļ�����·��  
            new_path = strcat(path,new_name);   %��ȡ���ļ�����·��  
            status = movefile(old_path,new_path); %ͨ���ƶ��ļ����������ļ�  
        end  
    case 'DR8'  
        files = dir([path '*']); %���������ļ�  
        n = length(files);           %�ļ�����  
        for i = 1:n  
            i  
            filename = [path files(i).name];    %�ļ���������·��  
            old_name = files(i).name;           %���������ļ���  
            pos_equal = strfind(old_name, '=');   %�ҵ�=��λ��   
            pos_and = strfind(old_name, '&');   %�ҵ�&��λ��  
            if length(pos_equal)~=3  
                continue;  
            end  
            pppp = old_name(pos_equal(1)+1:pos_and(1)-1);  
            pppp = alignbitzero(pppp ,4);  
            mmmmm = old_name(pos_equal(2)+1:pos_and(2)-1);  
            mmmmm = alignbitzero(mmmmm ,5);  
            ffff = old_name(pos_equal(3)+1:end);  
            ffff = alignbitzero(ffff ,4);  
  
            new_name = ['spec-' pppp '-' mmmmm '-' ffff '.fits'];  
            %��spec-��ʼֱ��������е��ַ�Ϊ�µ��ļ���  
            old_path = strcat(path,old_name);   %��ȡԭ���ļ�����·��  
            new_path = strcat(path,new_name);   %��ȡ���ļ�����·��  
            status = movefile(old_path,new_path); %ͨ���ƶ��ļ����������ļ�  
        end  
    case 'SPECIAL'  
        %Spec-2951-54592-433.fit  ---> spec-pppp-mmmmm-ffff.fits  
        files = dir([path '*.fit']); %���������ļ�  
        n = length(files);           %�ļ�����  
        for i = 1:n  
            i  
            filename = [path files(i).name];    %�ļ���������·��  
            old_name = files(i).name;           %���������ļ���  
            pos_equal = strfind(old_name, '-');   %�ҵ�=��λ��   
            pos_point = strfind(old_name, '.');   %�ҵ�.��λ��   
            if length(pos_equal)~=3  
                continue;  
            end  
            pppp = old_name(pos_equal(1)+1:pos_equal(2)-1);  
            pppp = alignbitzero(pppp ,4);  
            mmmmm = old_name(pos_equal(2)+1:pos_equal(3)-1);  
            mmmmm = alignbitzero(mmmmm ,5);  
            ffff = old_name(pos_equal(3)+1:pos_point-1);  
            ffff = alignbitzero(ffff ,4);  
  
            new_name = ['spec-' pppp '-' mmmmm '-' ffff '.fits'];  
            %��spec-��ʼֱ��������е��ַ�Ϊ�µ��ļ���  
            old_path = strcat(path,old_name);   %��ȡԭ���ļ�����·��  
            new_path = strcat(path,new_name);   %��ȡ���ļ�����·��  
            status = movefile(old_path,new_path); %ͨ���ƶ��ļ����������ļ�  
        end  
  
    otherwise  
        disp 'option error!'  
end  
end  
  
%old_num������������bitλ���Ͳ���,��alignbitzero(234,4)���ؽ����0234  
function new_num = alignbitzero(old_num, bit)  
len = length(old_num);  
if len > bit  
    disp 'error';  
end  
for i=1:bit-len  
    old_num=strcat('0', old_num);  
end  
new_num = old_num;  
end  
