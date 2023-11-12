clear all;
close all;
SNR=-5:5:20;
Mv=[4 16];
for j=1:length(Mv)
     M=Mv(j)
    TEBPSK=zeros(1,length(SNR));
      if M==4
          fft=128;
          a=16;
          b=16;
      elseif M==16
          fft=64;
          a=8;
          b=8;
      end
    for i=1:length(SNR)
        EbNo=SNR(i);
        sim('ofdm16');
        TEBPSK(i)=outsiml(1);

        if TEBPSK(i)==0
            TEBPSK(i)=1e-6;
        end
        
    end
    TEBPSK
    
     figure(1); semilogy(SNR,TEBPSK,'-*');hold on;
     %figure(2); semilogy(SNR,TEB16PSK,'-o');hold on;
     %figure(3); semilogy(SNR,TEBPSK,'-*');hold on;semilogy(SNR,TEBPSK,'-o');hold on;
    
end
     figure(1); legend('QPSK','16-PSK'); grid on; xlabel('SNR');ylabel('TEB')
    % figure(2); legend('QPSK','16-PSK'); grid on; xlabel('TEB');ylabel('SNR')