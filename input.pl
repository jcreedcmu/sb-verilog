use Time::HiRes qw(usleep);
$| = 1;
$n = 0;
while(1) {
  $n++;
  print "$n";
  usleep(250000);
}
