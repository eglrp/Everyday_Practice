
function histLBP=getLBPHist(I,r,c)
%ȡ��I������LBPֱ��ͼ
%
%���룺 r,c--��������Ŀ��r*c������
%
%���أ�histLBP---����I�ĸ����ֿ��LBPֱ��ͼ���γɵĴ���I��LBP������������

[m,n]=size(I);
%��������Ĵ�С
mPartitionSize=floor(m/r);
nPartitionSize=floor(n/c);
for ii=1:r-1
    for jj=1:c-1
        Sub=I((ii-1)*mPartitionSize+1:ii*mPartitionSize,(jj-1)*nPartitionSize+1:jj*nPartitionSize);
      %  hist{ii}{jj}=LBP();
    end
end

