//文字およびモールス符号、符号の長さの定義
String moji = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
//String tontu[] = "sl,lsss,lsls,lss,s,ssls,lls,ssss,ss,slll,lsl,slss,ll,ls,lll,slls,llsl,sls,sss,l,ssl,sssl,sll,lss,lsll,llss,k";
char tontu[][4] = {"sl", "lsss", "lsls", "lss", "s", "ssls", "lls", "ssss", "ss", "slll", "lsl", "slss", "ll", "ls", "lll", "slls", "llsl", "sls", "sss", "l", "ssl", "sssl", "sll", "lss", "lsll", "llss", "k"};
int mojisu[] =   {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 3, 4, 3, 3, 4, 4, 1};

//点灯時間の設定
int ton = 100; //単符 （s,１）
int tu = ton * 3; //長符（l,３）
int kyuhu = ton * 3; //文字間空白（３）
int kuhaku = ton * 4; //kyuhu+kuhaku = 単語間空白（k,７）

//LEDピン設定
int ledPin = 13;

//表示したい文字列設定（A~Z, 空白）
String tar = "ABC DE";
 
void setup() {
  pinMode(ledPin, OUTPUT);//13番ピン
  Serial.begin(9600);//デバッグ用のシリアル通信
}

void loop() {
  for (int i = 0; i < tar.length(); i++) { //一文字単位でモールス符号の配列場所読み取り
    int s = moji.indexOf(tar[i]); //モールス符号が書かれた文字列の場所が返ってくるはず（0～）
    Serial.println(moji[s]);
    showChr(s);
  }
}

void showChr(int s) { //一文字分の符号読み取りと投げる
  int leng = mojisu[s]; //文字数を読み取る（できれば配列から要素数で読み取りたい）
  Serial.println(leng);
  for (int j = 0; j < leng; j++) {
    showHugou(String(tontu[s][j]));//符号単位でshowHugouに投げる
  }
  Serial.println("Kyuhu");
  delay(kyuhu);//文字間空白
}

void showHugou(String chara) { //符号をもらって種類に応じて点灯させる。
  if (chara.equals("s")) {
    digitalWrite(ledPin, HIGH);
    Serial.println("short!");
    delay(ton);
    digitalWrite(ledPin, LOW);
  } else if (chara.equals("l")) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Long");
    delay(tu);
    digitalWrite(ledPin, LOW);
  } else if (chara.equals("k")) {
    Serial.println("Kuhaku");
    delay(kuhaku);
  } else {
    Serial.println("Kyuhu");
  }
  delay(ton);//符号間休符
}
