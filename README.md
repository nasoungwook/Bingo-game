# Bingo-game
C++ Bingo game

■ 빙고 게임 프로그램 개요
   1. 컴퓨터와 사용자가 경기를 진행한다.
2. 한 명씩 돌아가면서 숫자를 부르는 방식으로 진행한다.
3. 컴퓨터와 사용자의 빙고판의 크기는  5x5이며, 1~25의 숫자가 임의로 배열된다.
4. 숫자를 부르면 0이 표기 된다.
5. 대각선, 가로, 세로 중 3개 줄 이상의 숫자들이 모두 불렀을 때 빙고를 외치면 이긴다.
6. 빙고는 숫자를 부른 쪽이 먼저 외칠 수 있는 우선순위가 있다.
7. 컴퓨터는 똑같은 숫자를 부르지 않는다.
8. 숫자를 부르는 방식은 컴퓨터의 경우에 가로, 세로, 대각선의 0개 개수를 파악하여 0이 가장 많은 줄에 0을 넣게 하는 알고리즘으로 이루어진다.
9. 사용자는 키보드를 통해 숫자를 입력한다.

■ 구현한 클레스 설명
 ● Bingo 클래스는 빙고의 구현, 승패, 컴퓨터의 인공지능을 하는 역활을 
    포함하고 있다. 기본생성자, checkBingo, printBingoGrid, callNumber, 
    AI로 구성되어 있다.
1. 기본생성자
  -기본 생성자에는  bingoNum[5][5]에 중복 없는 난수를 넣고 그 외의 
   변수를 초기화 시킨다. 그리고 bingoNum[5][5]를 nStatus[5][5]에 복사
   시킨다.

2. int checkBingo()
   
  -  nStatus[5][5]를 이용하여 빙고를 부를 수 있는지 검사한다. 
     만약, 빙고면 return 1을 하고, 아니면 return 0을 한다.
3. void printBingoGrid()
  
 - nStatus[5][5]를 출력한다.
  
4. int callNumber(int number)
   
   
  - main에서 number를 받아들인다.
    그리고 bingoNum[5][5]의 숫자가 호출되었는지 검사하고 기록한다.
    number에 이상이 있으면 return 0, 없으면 return 1을 한다.
    (중복, 1~25 숫자가 아닌 경우, 문자가 입력된 경우)
5. int AI()
  - 컴퓨터의 [5][5]배열을 통해서 가로, 세로 대각선의 0개수를 파악하여
     0이 가장 많은 줄에 넣게 한다.
 ● Rnd 클래스는 1~25 숫자를 난수 생성하는 기능을 가진 클래스이다.
1. 기본 생성자
  - 1~25 까지 범위 초기화
2. get RNumber()
  - rand함수로 난수를 생성한다.
■ 메인함수
  -사용자가 숫자를 입력받고 숫자이면 입력을 하고, 
   0또는 문자이면 26을 넣어 준다.
  - callNumber가 0이면 다시 반복한다. 1이면 다음으로 넘어간다.
  - 사용자의 숫자를 컴퓨터에 넣어준다.
  - 사용자 또는 컴퓨터가 checkBingo가 1이면 빙고를 외친다.
  - 컴퓨터가 실행하고 나온 숫자를 사용자에 넣어준다.
  - 컴퓨터 또는 사용자가 checkBingo가 1이면 빙고를 외친다.
  - 승패가 날 때까지 무한반복 한다.
  
  http://blogfiles.naver.net/MjAxNzAxMTlfMTc4/MDAxNDg0ODExMjYwMjM1.YMlNQtjv1pOEZo6jt0l_ZR52A2q_iOeGYo6laFamO3Mg.r2hhKOgzeVAEDZb1lkEzAGX4XdcKXxwCELgfFQM0vN0g.PNG.wsn026/20170119_163342.png
