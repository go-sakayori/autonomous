#include "scan.h"

void scan_terrain(){
  int fd;
  struct ccmd cmd;
  struct uout obuf;

  //open USB device  
  if((fd = open("/dev/urbtc0", O_RDWR)) == -1){
    fprintf(stderr, "/dev/urbtc0: Open error\n");
    exit(1);
  }

  //initialize. 
  cmd = iXs_init_data();

  if(write(fd, &cmd, sizeof(cmd)) < 0){
    fprintf(stderr, "initialize error\n");
    exit(1);
  }

  obuf = gain_init_data();

  if (ioctl(fd, URBTC_DESIRE_SET) < 0)
    {
      fprintf(stderr, "ioctl: URBTC_DESIRE_SET error\n");
      exit(1);
    }

  if(write(fd, &obuf, sizeof(obuf)) <= 0)
    {
      fprintf(stderr, "write error\n");
      exit(1);
    }

  //urg_3d(fds, obuf);

  close(fd);
}

struct ccmd iXs_init_data()
{
  struct ccmd cmd;  
  cmd.retval = 0 /* RETURN_VAL */;
  cmd.setoffset  = CH0 | CH1 | CH2 | CH3;
  cmd.setcounter = CH0 | CH1 | CH2 | CH3;
  cmd.resetint   = CH0 | CH1 | CH2 | CH3;
  cmd.selin = SET_SELECT | CH0 | CH3; // 0:ENC, 1:A/D
  cmd.dout = 0;
  cmd.selout = SET_SELECT | CH0 | CH1 | CH2 | CH3; // 0:A/D,1:PWM 
  cmd.offset[0] = cmd.offset[1] = cmd.offset[2] = cmd.offset[3] = 0x7fff;
  cmd.counter[0] = cmd.counter[1] = cmd.counter[2] = cmd.counter[3] = 0;
  cmd.posneg = SET_POSNEG | CH0 | CH1 | CH2 | CH3;
  cmd.breaks = SET_BREAKS;
  cmd.wrrom = 0; 
        
  return cmd;
}

struct uout gain_init_data()
{
  struct uout obuf;  
  
  // gimbal and potentio
  obuf.ch[0].kp = 0;
  obuf.ch[0].kd = 0;
  obuf.ch[0].ki = 0;
  obuf.ch[0].kpx = 1;
  obuf.ch[0].kdx = 1;
  obuf.ch[0].kix = 1;
  obuf.ch[0].d = 0;
  obuf.ch[0].x = 0;
  // gimbal and encoder
  obuf.ch[1].kp = 0;
  obuf.ch[1].kd = -1;
  obuf.ch[1].ki = 0;
  obuf.ch[1].kpx = 1;
  obuf.ch[1].kdx = 1;
  obuf.ch[1].kix = 1;
  obuf.ch[1].d = 0;
  obuf.ch[1].x = 0;
  // free 
  obuf.ch[2].kp = 0;
  obuf.ch[2].kd = 0;
  obuf.ch[2].ki = 0;
  obuf.ch[2].kpx = 1;
  obuf.ch[2].kdx = 1;
  obuf.ch[2].kix = 1;
  obuf.ch[2].d = 0;
  obuf.ch[2].x = 0;
  // free
  obuf.ch[3].kp = 0;
  obuf.ch[3].kd = 0;
  obuf.ch[3].ki = 0;
  obuf.ch[3].kpx = 1;
  obuf.ch[3].kdx = 1;
  obuf.ch[3].kix = 1;
  obuf.ch[3].d = 0;
  obuf.ch[3].x = 0;

  return obuf;
}
