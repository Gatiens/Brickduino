#include <UTFT.h>                          //Graphics library
#include <URTouch.h>                       //Touch Screen library

//------------------------------------------------------------
//==== Creating Objects
//------------------------------------------------------------
UTFT    myGLCD(SSD1289, 38, 39, 40, 41);
URTouch  myTouch( 6, 5, 4, 3, 2);

//------------------------------------------------------------
//==== Defining Fonts
//------------------------------------------------------------
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

//------------------------------------------------------------
//===== Defining Pin
//------------------------------------------------------------
const int VCC = 13;                        //Power to periferals
const int YBTN = 12;                       //Yellow Button
const int GBTN = 11;                       //Green Button
const int RBTN = 10;                       //Red Button
const int JOY = 9;                         //Joystick Button
const int XPIN = A1;                       //Joystick X axis
const int YPIN = A0;                       //Joystick Y axis

//------------------------------------------------------------
//===== Defining Variables
//------------------------------------------------------------
float ballX = 160;                         //Ball X coordinates
float ballY = 160;                         //Ball Y coordianates
float oldBallX = ballX;                    //Balls old X position
float oldBallY = ballY;                    //Balls old Y position
float xincrement = 1.7;                    //X increment to move the ball
float yincrement = 1.7;                    //Y increment to move the ball
int rad = 3;                               //Ball radius
int score = 0;                             //Score in the game
int blockWidth = 28;                       //Width of a block
int blockHeight = 18;                      //Height of a block
int paddleWidth = 50;                      //Width of the padddle
int paddleHeight = 5;                      //Height of the paddle
int paddleX1 = 135;                        //Paddles X1 location
int paddleX2 = paddleX1 + paddleWidth;     //Paddles X2 location
int paddleY1 = 220;                        //Paddles Y1 location
int paddleY2 = paddleY1 + paddleHeight;    //Paddles Y2 location
int paddleX1Old = 135;                     //Paddles old X1 location
int paddleX2Old = paddleX1 + paddleWidth;  //Paddles old X2 location
int paddleY1Old = 220;                     //Paddles old Y1 location
int paddleY2Old = paddleY1 + paddleHeight; //Paddles old Y2 location
int numBlocks = 30;                        //Number of blocks in a level
int level = 1;                             //Current level
boolean continueGame = true;               //Game is not over
boolean menuVar = false;                   //Bool to play the Menu screen
boolean levelVar = false;                  //Bool to play the Level Select screen

//------------------------------------------------------------
//==== Brick Data for levels
//------------------------------------------------------------
char16_t bricks[40][4]; //Bricks to be displayed

//==== Level 1
char16_t bricks1[30][4] = {
  //---- in play, xloc, yloc, color
  {1,   10,    40,  VGA_LIME}    ,
  {1,   40,    40,  VGA_LIME}    ,
  {1,   70,    40,  VGA_LIME}    ,
  {1,   100,   40,  VGA_LIME}    ,
  {1,   130,   40,  VGA_LIME}    ,
  {1,   160,   40,  VGA_LIME}    ,
  {1,   190,   40,  VGA_LIME}    ,
  {1,   220,   40,  VGA_LIME}    ,
  {1,   250,   40,  VGA_LIME}    ,
  {1,   280,   40,  VGA_LIME}    ,
  {1,   10,    80,  VGA_PURPLE}  ,
  {1,   40,    80,  VGA_PURPLE}  ,
  {1,   70,    80,  VGA_PURPLE}  ,
  {1,   100,   80,  VGA_PURPLE}  ,
  {1,   130,   80,  VGA_PURPLE}  ,
  {1,   160,   80,  VGA_PURPLE}  ,
  {1,   190,   80,  VGA_PURPLE}  ,
  {1,   220,   80,  VGA_PURPLE}  ,
  {1,   250,   80,  VGA_PURPLE}  ,
  {1,   280,   80,  VGA_PURPLE}  ,
  {1,   10,    120, VGA_MAROON}  ,
  {1,   40,    120, VGA_MAROON}  ,
  {1,   70,    120, VGA_MAROON}  ,
  {1,   100,   120, VGA_MAROON}  ,
  {1,   130,   120, VGA_MAROON}  ,
  {1,   160,   120, VGA_MAROON}  ,
  {1,   190,   120, VGA_MAROON}  ,
  {1,   220,   120, VGA_MAROON}  ,
  {1,   250,   120, VGA_MAROON}  ,
  {1,   280,   120, VGA_MAROON}  };
  
//==== Level 2
char16_t bricks2[30][4] = {
  //----  in play, xloc, yloc, color
  {1,   10,    40,   VGA_BLUE}    ,
  {1,   40,    60,   VGA_LIME}    ,
  {1,   70,    40,   VGA_LIME}    ,
  {1,   100,   60,   VGA_PURPLE}  ,
  {1,   130,   40,   VGA_PURPLE}  ,
  {1,   160,   60,   VGA_FUCHSIA} ,
  {1,   190,   40,   VGA_FUCHSIA} ,
  {1,   220,   60,   VGA_AQUA}    ,
  {1,   250,   40,   VGA_AQUA}    ,
  {1,   280,   60,   VGA_OLIVE}   ,
  {1,   10,    80,   VGA_LIME}    ,
  {1,   40,    100,  VGA_PURPLE}  ,
  {1,   70,    80,   VGA_PURPLE}  ,
  {1,   100,   100,  VGA_FUCHSIA} ,
  {1,   130,   80,   VGA_FUCHSIA} ,
  {1,   160,   100,  VGA_AQUA}    ,
  {1,   190,   80,   VGA_AQUA}    ,
  {1,   220,   100,  VGA_OLIVE}   ,
  {1,   250,   80,   VGA_OLIVE}   ,
  {1,   280,   100,  VGA_NAVY}    ,
  {1,   10,    120,  VGA_PURPLE}  ,
  {1,   40,    140,  VGA_FUCHSIA} ,
  {1,   70,    120,  VGA_FUCHSIA} ,
  {1,   100,   140,  VGA_AQUA}    ,
  {1,   130,   120,  VGA_AQUA}    ,
  {1,   160,   140,  VGA_OLIVE}   ,
  {1,   190,   120,  VGA_OLIVE}   ,
  {1,   220,   140,  VGA_NAVY}    ,
  {1,   250,   120,  VGA_NAVY}    ,
  {1,   280,   140,  VGA_GREEN}   };
  
//==== Level 3
char16_t bricks3[30][4] = {
  //----  in play, xloc, yloc, color
  {1,   10,    120,  VGA_MAROON}  ,
  {1,   40,    120,  VGA_RED}     ,
  {1,   70,    120,  VGA_FUCHSIA} ,
  {1,   100,   120,  VGA_PURPLE}  ,
  {1,   130,   120,  VGA_BLUE}    ,
  {1,   160,   120,  VGA_NAVY}    ,
  {1,   190,   120,  VGA_TEAL}    ,
  {1,   220,   120,  VGA_AQUA}    ,
  {1,   250,   120,  VGA_LIME}    ,
  {1,   280,   120,  VGA_GREEN}   ,
  {1,   10,    140,  VGA_MAROON}  ,
  {1,   40,    140,  VGA_RED}     ,
  {1,   70,    140,  VGA_FUCHSIA} ,
  {1,   100,   140,  VGA_PURPLE}  ,
  {1,   130,   140,  VGA_BLUE}    ,
  {1,   160,   140,  VGA_NAVY}    ,
  {1,   190,   140,  VGA_TEAL}    ,
  {1,   220,   140,  VGA_AQUA}    ,
  {1,   250,   140,  VGA_LIME}    ,
  {1,   280,   140,  VGA_GREEN}   ,
  {1,   10,    160,  VGA_MAROON}  ,
  {1,   40,    160,  VGA_RED}     ,
  {1,   70,    160,  VGA_FUCHSIA} ,
  {1,   100,   160,  VGA_PURPLE}  ,
  {1,   130,   160,  VGA_BLUE}    ,
  {1,   160,   160,  VGA_NAVY}    ,
  {1,   190,   160,  VGA_TEAL}    ,
  {1,   220,   160,  VGA_AQUA}    ,
  {1,   250,   160,  VGA_LIME}    ,
  {1,   280,   160,  VGA_GREEN}   };
  
//==== Level 4
char16_t bricks4[40][4] = {
  //----  in play, xloc, yloc, color
  {1,   10,    40,   VGA_MAROON}  ,
  {1,   40,    40,   VGA_MAROON}  ,
  {1,   70,    40,   VGA_MAROON}  ,
  {1,   100,   40,   VGA_MAROON}  ,
  {1,   130,   40,   VGA_MAROON}  ,
  {1,   160,   40,   VGA_MAROON}  ,
  {1,   190,   40,   VGA_MAROON}  ,
  {1,   220,   40,   VGA_MAROON}  ,
  {1,   250,   40,   VGA_MAROON}  ,
  {1,   280,   40,   VGA_MAROON}  ,
  {1,   10,    60,   VGA_RED}     ,
  {1,   10,    80,   VGA_RED}     ,
  {1,   10,    100,  VGA_RED}     ,
  {1,   10,   120,   VGA_RED}     ,
  {1,   10,   140,   VGA_RED}     ,
  {1,   280,   60,   VGA_RED}     ,
  {1,   280,   80,   VGA_RED}     ,
  {1,   280,   100,  VGA_RED}     ,
  {1,   280,   120,  VGA_RED}     ,
  {1,   280,   140,  VGA_RED}     ,
  {1,   10,    160,  VGA_MAROON}  ,
  {1,   40,    160,  VGA_MAROON}  ,
  {1,   70,    160,  VGA_MAROON}  ,
  {1,   100,   160,  VGA_MAROON}  ,
  {1,   130,   160,  VGA_MAROON}  ,
  {1,   160,   160,  VGA_MAROON}  ,
  {1,   190,   160,  VGA_MAROON}  ,
  {1,   220,   160,  VGA_MAROON}  ,
  {1,   250,   160,  VGA_MAROON}  ,
  {1,   280,   160,  VGA_MAROON}  ,
  {1,   40,    60,   VGA_BLUE}    ,
  {1,   40,    80,   VGA_BLUE}    ,
  {1,   70,    100,  VGA_BLUE}    ,
  {1,   100,   120,  VGA_BLUE}    ,
  {1,   130,   140,  VGA_BLUE}    ,
  {1,   160,   140,  VGA_BLUE}    ,
  {1,   190,   120,  VGA_BLUE}    ,
  {1,   220,   100,  VGA_BLUE}    ,
  {1,   250,   80,   VGA_BLUE}    ,
  {1,   250,   60,   VGA_BLUE}    };

//------------------------------------------------------------
//Initital Setup for program, Runs on start
//------------------------------------------------------------
void setup() {
  //---- Initial setup of graphics and touch libraries
  myGLCD.InitLCD(LANDSCAPE);
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);

  //---- Defining Pin Modes
  pinMode(XPIN, INPUT);    //Joystick X pin input
  pinMode(YPIN, INPUT);    //Joystick Y pin input
  pinMode(JOY, INPUT);     //Joystick input
  pinMode(GBTN, INPUT);    //Green Button input
  pinMode(RBTN, INPUT);    //Red Button input
  pinMode(YBTN, INPUT);    //Yellow Button input

  pinMode(VCC, OUTPUT);    //Power output
  digitalWrite(VCC, HIGH); //+5V - Pin 13 as VCC

  resetBlocks();           //Loads brick data into bricks
  menuVar = true;          //Begin game with menu on
  myGLCD.clrScr();
  welcome();               //Plays welcome screen
}

//------------------------------------------------------------
//Loop that runs every frame
//------------------------------------------------------------
void loop() {
  //---- While loop to play Menu screen
  while ( menuVar == true && levelVar == false) {
    menuVar = playMenu();
  }
  
  //---- While loop to play Level Select screen 
  while ( levelVar == true && menuVar == false) {
    levelVar = playLevelSelect();
  }
  
  //---- Main loop for Brick Breaker
  if (continueGame && menuVar == false) {
    drawFrame();                                      //Draws paddle, ball, and bricks
    drawScore();                                      //Draws Score and Level
    movePaddle();                                     //Moves the paddle on inputs
    boolean paddleCollision = checkPaddleCollision(); //If the check comes back as true a collision has occured
    boolean blockCollision = checkBlockCollision();   //If the check comes back as true a collision has occured

    //---- If YBTN is set to high (pressed), sets MenuVar to true to play the menu
    if ( digitalRead(YBTN) == HIGH) {
      myGLCD.clrScr();
      menuVar = true;
    }

    //---- If score == numBlocks the level is beaten and plays a winner screen
    if (score == numBlocks)
      winner();
    else {
      //---- If either paddle or blockcollision came back as true, redraws the frame to reflect the collision
      if (paddleCollision || blockCollision)
        drawFrame();
      delay(50);
      continueGame = updatePos();                     //Checks for game loss and updates ball position
    }
  }
  else
    gameOver();
}

//------------------------------------------------------------
//Resets all variables for the paddle,
//blocks and ball to restart the game
//------------------------------------------------------------
void reset() {
  ballX = 160;
  ballY = 160;
  oldBallX = ballX;
  oldBallY = ballY;
  xincrement = 1.7;
  yincrement = 1.7;
  score = 0;
  paddleX1 = 135;
  paddleX2 = paddleX1 + paddleWidth;
  paddleY1 = 220;
  paddleY2 = paddleY1 + paddleHeight;
  paddleX1Old = 135;
  paddleX2Old = paddleX1 + paddleWidth;
  paddleY1Old = 220;
  paddleY2Old = paddleY1 + paddleHeight;
  continueGame = true;
  resetBlocks();
}

//------------------------------------------------------------
//Updates the balls position and applies collison to the ball
//------------------------------------------------------------
boolean updatePos() {
  //---- If the ball touches the sides (left and right) of the screen
  if (ballX > 320 - rad * 2 || ballX < 0 + rad * 2)
    xincrement = -xincrement;

  //---- If the ball hits the bottom, Game Over
  if (ballY > 240)
    return false;
    
  //---- If the ball hit the top of the screen
  else if (ballY < 11 + rad * 2)
    yincrement = -yincrement;

  //---- Sets oldBall as balls current position
  oldBallX = ballX;
  oldBallY = ballY;

  //---- Updates the ball with new position
  ballX += xincrement;
  ballY += yincrement;

  return true;
}

//------------------------------------------------------------
// Checks to see if the ball has hit the paddle
//------------------------------------------------------------
boolean checkPaddleCollision() {
  //---- Defines values for easy reference
  int ballTop = ballY - rad;
  int ballBottom = ballY + rad;
  int ballLeft = ballX - rad;
  int ballRight = ballX + rad;
  int middleOffset = 5;

  if (ballBottom >= paddleY1 && ballTop <= paddleY1) {         //If the ball is hitting the TOP of the paddle
    if (ballX >= paddleX1 && ballX <= paddleX2) {              //If the ball has hit in between the left and right edge of paddle
      float paddleMidPoint = (paddleX1 + paddleWidth - 1) / 2; //Determines paddle midpoint to determine whether to flip X direction
      yincrement = - yincrement;                               //Flip Y increment
      if (ballX <= paddleMidPoint - middleOffset)              //If the ball's xloc is less than the paddle's mid point, flip the x direction
        xincrement = -xincrement;
      return true;
    }
    if (ballRight >= paddleX1 && ballLeft < paddleX1) {        //If the ball is hitting the LEFT of the paddle
      if (xincrement > 0)                                      //If the ball is coming from the left, flip X
        xincrement = -xincrement;
      yincrement = -yincrement;
      return true;
    }
    else if (ballLeft <= paddleX2 && ballRight > paddleX2) {   //If the ball is hitting the RIGHT of the paddle
      if (xincrement < 0)                                      //If it's coming from the right, flip x
        xincrement = -xincrement;
      yincrement = -yincrement;
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------
// Checks to see if the ball has collided with a block
//------------------------------------------------------------
boolean checkBlockCollision() {
  //Values for easy reference
  int ballTop = ballY - rad;
  int ballBottom = ballY + rad;
  int ballLeft = ballX - rad;
  int ballRight = ballX + rad;

  for (int i = 0; i < numBlocks; i++) {                                    //Loops through the blocks
    if (bricks[i][0] == 1) {                                               //If the block has not been destroyed
      int blockX = bricks[i][1];                                           //Grab X and Y location
      int blockY = bricks[i][2];

      if (ballBottom >= blockY && ballTop <= (blockY + blockHeight)) {     //If the ball is hitting a block
        if (ballRight >= blockX && ballLeft <= (blockX + blockWidth)) {
          removeBlock(i);                                                  //Removes block from play

          //---- Needs work to improve corner detection
          if (ballRight >= blockX && ballRight >= (blockX + blockWidth)) { //If the ball is hitting the Right of the block, flip x
            xincrement = -xincrement;
            return true;
          } else {                                                         //Else ball is hitting the top or bottom of the block, flip Y
            yincrement = -yincrement;
            return true;
          }
        }
      }
    }
  }
  return false;
}

//------------------------------------------------------------
//Removes block at index from the game
//------------------------------------------------------------
void removeBlock(int index) {
  myGLCD.setColor(0, 0, 0);     //Sets color to black

  //---- Redraws the brick as black to remove it from the game
  myGLCD.fillRect(bricks[index][1], bricks[index][2],
                  bricks[index][1] + blockWidth, bricks[index][2] + blockHeight );
                  
  bricks[index][0] = 0;         //Brick no longer in play
  score++;                      //Increase score
  adjustSpeed();                //Adjusts ball speed
}

//------------------------------------------------------------
//Moves the paddle
//------------------------------------------------------------
void movePaddle() {
  //---- Saves paddle old location
  paddleX1Old = paddleX1;
  paddleX2Old = paddleX2;

  //---- If the Joystick is to the left
  if (int(analogRead(XPIN)) > 411) {
    if (paddleX1 < 275)
      paddleX1 += 10;
  }
  //---- If the Joystick is to the right.
  //(note: left a gap in the middle to reduce joystick sensitivity when slightly moving it)
  if (int(analogRead(XPIN)) < 611) {
    if (paddleX1 > 5)
      paddleX1 -= 10;
  }
  paddleX2 = paddleX1 + paddleWidth;
}

//------------------------------------------------------------
//Adjusts the speed of the ball
//------------------------------------------------------------
void adjustSpeed() {
  if (yincrement < 0)     //If yincrement is negative
    yincrement -= 0.09;
  else                    //Else it is positive
    yincrement += 0.09;
    
  if (xincrement < 0)     //If xincrement is negative
    xincrement -= 0.09;
  else                    //Else it is positive
    xincrement += 0.09;

  Serial.print(xincrement);
  Serial.print(" ");
  Serial.println(yincrement);
}

//------------------------------------------------------------
//Reset all the blocks
//------------------------------------------------------------
void resetBlocks() {
  //==== Level 1
  if (level == 1) {
    numBlocks = 30;
    for (byte entity = 0; entity < numBlocks; entity++) { //Loop through and deep copy into the block array.
      for (byte data = 0; data <= 4; data++) {
        bricks[entity][data] = bricks1[entity][data];     //Sets bricks to bricks to load level 1
      }
    }
  }
  
  //==== Level 2
  else if (level == 2) {
    ballY = 200;                                          //Move ball starting position down
    numBlocks = 30;
    for (byte entity = 0; entity < numBlocks; entity++) { //Loop through and deep copy into the block array.
      for (byte data = 0; data <= 4; data++) {
        bricks[entity][data] = bricks2[entity][data];     //Sets bricks to bricks to load level 2
      }
    }
  }
  
  //==== Level 3
  else if (level == 3) {
    ballY = 190;
    numBlocks = 30;
    for (byte entity = 0; entity < numBlocks; entity++) { //Loop through and deep copy into the block array.
      for (byte data = 0; data <= 4; data++) {
        bricks[entity][data] = bricks3[entity][data];     //Sets bricks to bricks to load level 3
      }
    }
  }
  
  //==== Level 4
  else if (level == 4) {
    ballY = 100;
    numBlocks = 40;
    for (byte entity = 0; entity < numBlocks; entity++) { //Loop through and deep copy into the block array.
      for (byte data = 0; data <= 4; data++) {
        bricks[entity][data] = bricks4[entity][data];     //Sets bricks to bricks to load level 4
      }
    }
  }
}

//------------------------------------------------------------
//Plays and draws the Menu screen.
//Returns false to exit the menu
//------------------------------------------------------------
boolean playMenu() {
  int x, y;
  drawMenu();                               //draws the menu

  //---- If statement for Touch Screen Data collection
  if (myTouch.dataAvailable()) {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();

    //==== Button 1 functionality
    if ((x >= 35) && (x <= 285) && (y >= 40) && (y <= 80)) {
      drawHighlightFrame(35, 40, 285, 80);  //Custom Function Highlighs the buttons when it's pressed
      myGLCD.clrScr();
      return false;
    }

    //==== Button 2 functionality
    if ((x >= 35) && (x <= 285) && (y >= 90) && (y <= 130)) {
      drawHighlightFrame(35, 90, 285, 130);
      myGLCD.clrScr();
      levelVar = true;
      return false;
    }

    //==== Button 3 functionality
    if ((x >= 35) && (x <= 285) && (y >= 140) && (y <= 180)) {
      drawHighlightFrame(35, 140, 285, 180);
      myGLCD.clrScr();
      return false;
    }

    //==== Button 4 functionality
    if ((x >= 35) && (x <= 285) && (y >= 190) && (y <= 230)) {
      drawHighlightFrame(35, 190, 285, 230);
      myGLCD.clrScr();
      return false;
    }
  }

  //---- If the Yellow of Red Button are pressed in the menu, returns false to exit the menu.
  if ( digitalRead(YBTN) == HIGH || digitalRead(RBTN) == HIGH) {
    myGLCD.clrScr();
    return false;
  } else {
    return true;
  }
}

//------------------------------------------------------------
//Plays and draws the Level Select screen,
//Returns false to exit the menu
//------------------------------------------------------------
boolean playLevelSelect() {
  int x, y;
  drawLevelSelect();

  //---- If statement for Touch Screen Data collection
  if (myTouch.dataAvailable()) {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();

    //==== Level 1
    if ((x >= 35) && (x <= 285) && (y >= 40) && (y <= 80)) {
      drawHighlightFrame(35, 40, 285, 80);              //Custom Function Highlighs the buttons when it's pressed
      myGLCD.clrScr();                                  //Clear Screen
      level = 1;                                        //Sets level to 1
      reset();                                          //Resets data
      return false;
    }

    //==== Level 2 ---- See Level 1 for comments
    if ((x >= 35) && (x <= 285) && (y >= 90) && (y <= 130)) {
      drawHighlightFrame(35, 90, 285, 130);
      myGLCD.clrScr();
      level = 2;
      reset();
      return false;
    }

    //==== Level 3 ---- See Level 1 for comments
    if ((x >= 35) && (x <= 285) && (y >= 140) && (y <= 180)) {
      drawHighlightFrame(35, 140, 285, 180);
      myGLCD.clrScr();
      level = 3;
      reset();
      return false;
    }

    //==== Level 4 ---- See Level 1 for comments
    if ((x >= 35) && (x <= 285) && (y >= 190) && (y <= 230)) {
      drawHighlightFrame(35, 190, 285, 230);
      myGLCD.clrScr();
      level = 4;
      reset();
      return false;
    }
  }

  //---- If the Yellow of Red Button are pressed in the menu, returns false to exit the menu.
  if ( digitalRead(YBTN) == HIGH || digitalRead(RBTN) == HIGH) {
    myGLCD.clrScr();
    return false;
  } else {
    return true;
  }
}

//------------------------------------------------------------
//Prints the data in bricks, Used for testing
//------------------------------------------------------------
void printBlocks() {
  int temp = 2;
  for (int i = 0; i < numBlocks; i++) {
    myGLCD.setFont(SmallFont);
    myGLCD.printNumI(bricks[i][1], 200, temp += 10);
  }
}

//==== Draw Functions ========================================
//------------------------------------------------------------
//Draws the Ball, Paddle, and Bricks
//------------------------------------------------------------
void drawFrame() {
  //---- Draw over old Ball, Paddle
  myGLCD.setColor(0, 0, 0);                                                 //Set color to black
  myGLCD.fillCircle(oldBallX, oldBallY, rad);                               //Draw over old circle
  myGLCD.fillRoundRect(paddleX1Old, paddleY1Old, paddleX2Old, paddleY2Old); //Draw over old paddle

  //---- Draw new Ball, Paddle
  myGLCD.setColor(255, 255, 255);                                           //Set color to white
  myGLCD.fillCircle(ballX, ballY, rad);                                     //Draw new circle
  myGLCD.fillRoundRect(paddleX1, paddleY1, paddleX2, paddleY2);             //Draw new paddle

  //---- Prints the bricks
  for (int i = 0; i < numBlocks; i++) {                                     //For each brick
    if (bricks[i][0] == 1) {                                                //If brick is still active
      myGLCD.setColor(bricks[i][3]);
      myGLCD.fillRect(bricks[i][1], bricks[i][2], bricks[i][1] +
                      blockWidth, bricks[i][2] + blockHeight );             //Draws brick into game
    }
  }
}

//------------------------------------------------------------
//Draws the score in the Top Right corner
//------------------------------------------------------------
void drawScore() {
  myGLCD.setColor(255, 255, 255);   //Sets color to white
  myGLCD.setBackColor(0, 0, 0);     //Background color to black
  myGLCD.setFont(SmallFont);        //Sets font as small
  myGLCD.print("Score:", 0, 0);     //Prints Score
  myGLCD.printNumI(score, 48, 0);   //Prints the Score number
  myGLCD.print ("Level:", 260, 0);  //Prints Level
  myGLCD.printNumI(level, 310, 0);  //Prints the Level number
  myGLCD.drawLine(0, 11, 319, 11);  //Draws white line at top of screen
}

//------------------------------------------------------------
//Draws a welcome screen when the game begins
//------------------------------------------------------------
void welcome() {
  myGLCD.setBackColor(0, 0, 0);                         //Sets the background color to black
  myGLCD.setColor(255, 255, 255);                       //Sets color to white
  myGLCD.setFont(BigFont);                              //Sets font to big
  myGLCD.print("Get Ready to play...", CENTER, 100);    //Prints the string on the screen
  delay(500);
  myGLCD.clrScr();
  myGLCD.print("BrickDuino!", CENTER, 100);
  delay(500);
  myGLCD.clrScr();
  reset();                                              //Resets data
}

//------------------------------------------------------------
//Draws the "Game Over" screen
//------------------------------------------------------------
void gameOver() {
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);                //Sets font to big
  myGLCD.print("Game Over!", CENTER, 100);
  delay(1000);
  myGLCD.print("Hold Green Button", CENTER, 120);
  delay(500);
  myGLCD.print("To Continue...", CENTER, 140);
  delay(500);
  //---- If Green Button is held the game will reset and start again.
  if ( digitalRead(GBTN) == HIGH) {
    myGLCD.clrScr();
    reset();
  }
}

//------------------------------------------------------------
//Draws winner screen
//------------------------------------------------------------
void winner() {
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);                //Sets font to big
  myGLCD.print("You Win!!", CENTER, 100);
  delay(1000);
  myGLCD.print("Hold Green Button", CENTER, 120);
  delay(500);
  myGLCD.print("To Continue...", CENTER, 140);
  delay(500);
  //---- If Green Button is held the game will reset and start again.
  if ( digitalRead(GBTN) == HIGH) {
    myGLCD.clrScr();
    reset();
  }
}
//------------------------------------------------------------
//Draws the Menu screen
//------------------------------------------------------------
void drawMenu() {
  //---- Title
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(BigFont);            //Sets font to big
  myGLCD.print("Brick-Breaker Menu", CENTER, 5);
  myGLCD.drawLine(0, 22, 319, 22);

  //---- Button 1
  myGLCD.setColor(56, 132, 252);              //Sets green color
  myGLCD.fillRoundRect (35, 40, 285, 80);     //Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255);             //Sets color to white
  myGLCD.drawRoundRect (35, 40, 285, 80);     //Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setBackColor(56, 132, 252);          //Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("Start New Game", CENTER, 52); //Prints the string

  //---- Button 2 ---- See Button 1 for comments
  myGLCD.setColor(56, 132, 252);
  myGLCD.fillRoundRect (35, 90, 285, 130);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 90, 285, 130);
  myGLCD.print("Level Select", CENTER, 102);

  //---- Button 3 ---- See Button 1 for comments
  myGLCD.setColor(56, 132, 252);
  myGLCD.fillRoundRect (35, 140, 285, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 140, 285, 180);
  myGLCD.print("Reset Level", CENTER, 152);

  //---- Button 4 ---- See Button 1 for comments
  myGLCD.setColor(56, 132, 252);
  myGLCD.fillRoundRect (35, 190, 285, 230);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 190, 285, 230);
  myGLCD.print("Back to Game", CENTER, 202);

  myGLCD.setBackColor(0, 0, 0); //sets background color back to black
}

//------------------------------------------------------------
//Custom Function used to highlight a button when it is pressed
//------------------------------------------------------------
void drawHighlightFrame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

  //---- While touch data is available
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

//------------------------------------------------------------
//Draws the Level Select screen
//------------------------------------------------------------
void drawLevelSelect() {
  //---- Title
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Level Select", CENTER, 5);
  myGLCD.drawLine(0, 22, 319, 22);

  //---- Button 1
  myGLCD.setColor(56, 132, 252);           // Sets green color
  myGLCD.fillRoundRect (35, 40, 285, 80);  // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255);          // Sets color to white
  myGLCD.drawRoundRect (35, 40, 285, 80);  // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setBackColor(56, 132, 252);       // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("Level 1", CENTER, 52);     // Prints the string

  //---- Button 2 ---- See Button 1 for comments
  myGLCD.setColor(56, 132, 252);
  myGLCD.fillRoundRect (35, 90, 285, 130);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 90, 285, 130);
  myGLCD.print("Level 2", CENTER, 102);

  //---- Button 3 ---- See Button 1 for comments
  myGLCD.setColor(56, 132, 252);
  myGLCD.fillRoundRect (35, 140, 285, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 140, 285, 180);
  myGLCD.print("Level 3", CENTER, 152);

  //---- Button 4 ---- See Button 1 for comments
  myGLCD.setColor(56, 132, 252);
  myGLCD.fillRoundRect (35, 190, 285, 230);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 190, 285, 230);
  myGLCD.print("Level 4", CENTER, 202);

  myGLCD.setBackColor(0, 0, 0);            //sets background color back to black
}




