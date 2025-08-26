struct file {
  int descriptor;
  string name;
  padding(8);
};
check_sizeof(32, struct file);
