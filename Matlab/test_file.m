file = dir('*.txt');
len = length(file);
for i = 1 : len
    oldname = file(i).name;
    newname = strcat('RH_', oldname);
    % '!'����˼�ǵ���ϵͳ������32��ASCII��ֵ����ʾ�ո�
    eval(['!rename' strcat(',',oldname)   strcat(',',newname)]);
    
    %cmd=['rename ',oldname, newname];
    %status = system(cmd);

end

% clc; clear;
% name1 = ' lyq.txt';
% name2 = ' lyq1.txt';
% eval(['!rename', name1 name2]);