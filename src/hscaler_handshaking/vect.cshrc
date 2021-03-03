#! /bin/tcsh

echo -n "enter 1 or 2 or 3: "
set num=$<;
switch($num)
case 1:
cp /home/w/c++/SystemC/hscaler_SystemC/vect/0001/input.bmp \
   /home/w/c++/SystemC/hscaler_SystemC/vect/0001/param.txt \
   /home/w/c++/SystemC/hscaler_SystemC/vect/0001/exp.bmp \
   /home/w/c++/SystemC/hscaler_SystemC/src/hscaler_handshaking/
breaksw
case 2:
cp /home/w/c++/SystemC/hscaler_SystemC/vect/0002/input.bmp \
   /home/w/c++/SystemC/hscaler_SystemC/vect/0002/param.txt \
   /home/w/c++/SystemC/hscaler_SystemC/vect/0002/exp.bmp \
   /home/w/c++/SystemC/hscaler_SystemC/src/hscaler_handshaking/
breaksw
case 3:
cp /home/w/c++/SystemC/hscaler_SystemC/vect/0003/input.bmp \
   /home/w/c++/SystemC/hscaler_SystemC/vect/0003/param.txt \
   /home/w/c++/SystemC/hscaler_SystemC/vect/0003/exp.bmp \
   /home/w/c++/SystemC/hscaler_SystemC/src/hscaler_handshaking/
breaksw
default:
echo "enter the requested number!"
breaksw
endsw


