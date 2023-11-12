#define SER 18 // data
#define SCK 21
#define RCK 19
#define NB595 4 //c1 , c2 , c3 , l
#define t 0
#define b1 4
#define b2 2
#define d e l a i 100
#define d e l a i 2 500
unsigned long l [ 8 ] ;
unsigned long l 2 [ 8 ] ;
unsigned long l 3 [ 8 ] ;
unsigned long cur , pre ;
void setup ( ) {
pinMode (SER,OUTPUT) ;
pinMode (RCK,OUTPUT) ;
pinMode (SCK,OUTPUT) ;
pinMode ( b1 , INPUT) ;
pinMode (b2,INPUT) ;
l[0]=0 b00000000011101000001010000100111 ;
l[1]=0 b00000000100001000001010000101000 ;
l[2]=0 b00000000100001000001011000101000 ;
l[3]=0 b00000000100001000001010100100100 ;
l[4]=0 b00000000100001000001010010100010 ;
l[5]=0 b00000000100000100010010001100001 ;
l[6]=0 b00000000100000010100010000100001 ;
l[7]=0 b00000000011100001000010000101110 ;
l2[0]=0 b00000000011111001000001000000000 ;
l2[1]=0 b00000000100000001000001000000000 ;
l2[2]=0 b00000000100000001000001000000000 ;
l2[3]=0 b00000000100000001000001000000000 ;
l2[4]=0 b00000000100000001000001000000000 ;
l2[5]=0 b00000000100000000100010000000000 ;
l2[6]=0 b00000000100000000010100000000000 ;
l2[7]=0 b00000000011111000001000000000000 ;
l3[0]=0 b00000000000000000001000000000000 ;
l3[1]=0 b00000000000000000010100000000000 ;
l3[2]=0 b00000000000000000101010000000000 ;
l3[3]=0 b00000000000000001001001000000000 ;
l3[4]=0 b00000000000000010001000100000000 ;
l3[5]=0 b00000000000000100000000010000000 ;
l3[6]=0 b00000000000001000001000001000000 ;
l3[7]=0 b00000000000011111111111111100000 ;
Serial.begin(250000);
}
void loop ( ) {
i f ( analogRead ( b1)>=3000){
cur=millis ( ) ;
pre=cur ;
while (cur−pre<=delai){
afficherCVNS () ;
cur=millis();
}
} elseif( analogRead ( b2)>=3000){
cur=millis();
pre=cur;
while(cur−pre<=delai){
afficherCV( ) ;
cur=millis() 
}
}else{
cur=millis() ;
pre=cur;
while ( cur−pre<=delai2 && analogRead (b2)<3000 && analogRead ( b1)<3000){
afficherAtt( ) ;
cur=millis( ) ;
}
cur=millis( ) ;
pre=cur;
while (cur−pre<=delai2 && analogRead (b2)<3000 && analogRead (b1)<3000){
afficherVoid( ) ;
cur=millis( ) ;
}
}
}
void afficherAtt() {
for ( int j =0; j <8; j++){
unsigned long ligne=(( long)1<<(7−j ) ) ;
unsigned long colonnes=~l3[j]& 0 b00000000111111111111111111111111 ;
write4_595 (SER,SCK,RCK,NB595 , colonne s<<8 | l i g n e ) ;
// S e r i a l . p r i n t l n ( colonne s | l i gne <<24 ,BIN) ;
}
}
void afficherVoid ( ) {
write4_595 (SER,SCK,RCK,NB595 , 0 ) ;
// S e r i a l . p r i n t l n ( colonne s | l i gne <<24 ,BIN) ;
}
void afficherCVNS ( ) {
for ( int j =0; j <8; j++){
unsigned long ligne=(( long)1<<(7−j ) ) ;
unsigned long colonnes=~l[j] & 0 b00000000111111111111111111111111 ;
write4_595 (SER,SCK,RCK,NB595 , colonne s<<8 | l i g n e ) ;
// S e r i a l . p r i n t l n ( colonne s | l i gne <<24 ,BIN) ;
}
}
void afficherCV ( ) {
for ( int j =0; j <8; j++){
unsigned long ligne=((long)1<<(7−j ) ) ;
unsigned long colonnes=~l2[j] & 0 b00000000111111111111111111111111 ;
write4_595 (SER,SCK,RCK,NB595 , colonne s<<8 |ligne);
// S e r i a l . p r i n t l n ( colonne s | l i gne <<24 ,BIN) ;
}
}
void write4_595 ( byte serPin , byte sckPin , byte rckPin , byte nb595 , unsigned long Data ){
// S e r i a l . p r i n t l n (Data ,BIN) ;
// b y t e t=0;
for (int i=0; i <8∗nb595 ; i++){//S . p r i n t ( (Data>>i )&1);∗
// S e r i a l . p r i n t ( (Data>>i )&1 ,BIN) ;
digitalWrite(serPin,(Data>>i)&1) ;
delay(t);
digitalWrite(sckPin,1);
delay(t);
digitalWrite(serPin,0);
delay(t);
digitalWrite(sckPin,0) ;
delay(t) ;
}
// S e r i a l . p r i n t l n ( ) ;
digitalWrite(rckPin,1);
delay(t);
digitalWrite(rckPin,0);
delay(t);
}
