struct ymenvelope_t {
  // the total level. <128
  unsigned char tl;
  // the rate scaling
  unsigned char rs;
  // the attack rate
  unsigned char ar;
  // the first decay rate
  unsigned char d1r;
  // amplitude modulation enable
  unsigned char am;
  // secondary decay rate
  unsigned char d2r;
  // secondary amplitude
  unsigned char d1l;
  // release rate
  unsigned char rr;
}

typedef struct ymenvelope_t ymenvelope_t;
typedef struct ymenvelope_t ymenvelope;
