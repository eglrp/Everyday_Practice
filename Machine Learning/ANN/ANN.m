% %����ָ�����������㣬����ͼ�л��
% X = [0 1; 0 1]; % ���������ĵķ�Χ
% clusters = 5; % ָ�������Ŀ
% points = 10; % ָ��ÿһ��ĵ����Ŀ
% std_dev = 0.05; % ÿһ��ı�׼��
% P = nngenc(X,clusters,points,std_dev);
% plot(P(1,:),P(2,:),'+r');
% title('������������');
% xlabel('p(1)');
% ylabel('p(2)');
% 
% %��������
% net=newc([0 1;0 1],5,0.1); %������Ԫ��ĿΪ5
% %�õ�����Ȩֵ������ͼ�ϻ��
% figure;
% plot(P(1,:),P(2,:),'+r');
% w=net.iw{1}
% hold on;
% plot(w(:,1),w(:,2),'ob');
% hold off;
% title('����������������ʼȨֵ');
% xlabel('p(1)');
% ylabel('p(2)');
% figure;
% plot(P(1,:),P(2,:),'+r');
% hold on;
% 
% %ѵ������
% net.trainParam.epochs=7;
% net=init(net);
% net=train(net,P);
% %�õ�ѵ���������Ȩֵ������ͼ�ϻ��
% w=net.iw{1}
% plot(w(:,1),w(:,2),'ob');
% hold off;
% title('�����������������º��Ȩֵ');
% xlabel('p(1)');
% ylabel('p(2)');
% a=0;
% p = [0.6 ;0.8];
% a=sim(net,p)
% 
% 
% %**************ָ�������ά�����������*******************
% P = [-3 -2 -2 0 0 0 0 +2 +2 +3;
% 0 +1 -1 +2 +1 -1 -2 +1 -1 0];
% C = [1 1 1 2 2 2 2 1 1 1];
% %����Щ���ת����ѧϰ������������ʹ�õ�Ŀ������
% T = ind2vec(C)
% %�ò�ͬ����ɫ�������Щ��������
% plotvec(P,C),
% title('�����ά����');
% xlabel('P(1)');
% ylabel('P(2)');
% 
% %��������
% net = newlvq(minmax(P),4,[.6 .4],0.1);
% %��ͬһ��ͼ�ϻ��������������ʼȨ������
% figure;
% plotvec(P,C)
% hold on
% W1=net.iw{1};
% plot(W1(1,1),W1(1,2),'ow')
% title('�����Լ�Ȩ������');
% xlabel('P(1), W(1)');
% ylabel('P(2), W(2)');
% hold off;
% 
% %ѵ�����磬���ٴλ��Ȩ������
% figure;
% plotvec(P,C);
% hold on;
% net.trainParam.epochs=150;
% net.trainParam.show=Inf;
% net=train(net,P,T);
% plotvec(net.iw{1}',vec2ind(net.lw{2}),'o');
% %����һ���ض��ĵ㣬�õ���������
% p = [0.8; 0.3];
% a = vec2ind(sim(net,p))
% 
% %%%%%%%%%**********�������1000����ά��������Ϊ�������������ֲ�*************
% P = rands(2,1000);
% plot(P(1,:),P(2,:),'+r')
% title('��ʼ���������ֲ�');
% xlabel('P(1)');
% ylabel('P(2)');
% 
% %�������磬�õ���ʼȨֵ
% net=newsom([0 1; 0 1],[5 6]);
% w1_init=net.iw{1,1}
% %�����ʼȨֵ�ֲ�ͼ
% figure;
% plotsom(w1_init,net.layers{1}.distances)
% %�ֱ�Բ�ͬ�Ĳ�����ѵ�����磬�����Ӧ��Ȩֵ�ֲ�ͼ
% for i=10:30:100
%     net.trainParam.epochs=i;
%     net=train(net,P);
%     figure;
%     plotsom(net.iw{1,1},net.layers{1}.distances)
% end
% %����ѵ���õ����磬ѡ���ض��������������õ������������
% p=[0.5;0.3];
% a=0;
% a = sim(net,p)
% 

%��ȡѵ������
[f1,f2,f3,f4,class] = textread('iris.txt' , '%f,%f,%f,%f,%d',150); %���ݸ�ʽ�Ͷ��뷽ʽ��ͬ

%����ֵ��һ��
[input,minI,maxI] = premnmx( [f1 , f2 , f3 , f4 ]')  ;

%�����������
s = length( class) ;
output = zeros( s , 3  ) ;
for i = 1 : s 
   output( i , class( i )  ) = 1 ;
end

%����������
net = newff( minmax(input) , [10 3] , { 'logsig' 'purelin' } , 'traingdx' ) ; 

%����ѵ������
net.trainparam.show = 50 ;
net.trainparam.epochs = 500 ;
net.trainparam.goal = 0.01 ;
net.trainParam.lr = 0.01 ;

%��ʼѵ��
net = train( net, input , output' ) ;

%��ȡ��������
[t1 t2 t3 t4 c] = textread('iris.txt' , '%f,%f,%f,%f,%f',150);

%�������ݹ�һ��
testInput = tramnmx ( [t1,t2,t3,t4]' , minI, maxI ) ;

%����
Y = sim( net , testInput ) 

%ͳ��ʶ����ȷ��
[s1 , s2] = size( Y ) ;
hitNum = 0 ;
for i = 1 : s2
    [m , Index] = max( Y( : ,  i ) ) ;
    if( Index  == c(i)   ) 
        hitNum = hitNum + 1 ; 
    end
end
sprintf('ʶ������ %3.3f%%',100 * hitNum / s2 )
