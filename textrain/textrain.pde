import processing.video.*;
Capture myCapture; 

Particle particles[]; 
int nParticles; 
int threshold; 

//============================================
void setup() {
  size(640, 480); 
  myCapture = new Capture(this, width, height);
  myCapture.start();
  threshold = 30;  

  String letters = "Anderson Ranch!";
  nParticles = letters.length(); 
  particles = new Particle[nParticles]; 
  for (int i=0; i<nParticles; i++) {
    float x = map(i, -1, nParticles, 0, width); 
    float y = 0; 
    char c = letters.charAt(i); 
    particles[i] = new Particle(x, y, c);
  }
}

//============================================
void draw() {
  if (myCapture.available() == true) {
    myCapture.read();
    myCapture.loadPixels();
    image(myCapture, 0, 0); 

    for (int i=0; i<nParticles; i++) {
      particles[i].update(); 
      particles[i].render();
    }
  }
}

//============================================
class Particle {
  float px; 
  float py;
  char  myLetter; 

  Particle (float x, float y, char c) {
    px = x; py = y; 
    myLetter = c;
  }

  void update() {
    if ((py >= height) || (py < 0)) {
      py = 0;
    }
     
    int myPixelIndex = (int)py * width + (int) px;
    color myPixelColor = myCapture.pixels[myPixelIndex]; 
    float myPixelBrightness = brightness(myPixelColor);
    float speed = 2.0; 
    if (myPixelBrightness > threshold) {
      py = py + speed;
    } else {
      while ( (myPixelBrightness <= threshold) && (py >= speed)) {
        myPixelIndex = (int)py * width + (int) px;
        myPixelColor = myCapture.pixels[myPixelIndex]; 
        myPixelBrightness = brightness(myPixelColor);
        py = py - speed;
      }
    }
  }

  void render() {
    fill (0); 
    text (myLetter, px+1, py+1); 
    fill (255); 
    text (myLetter, px, py);
  }
}

