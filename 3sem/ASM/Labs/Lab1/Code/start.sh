cp -r ../../TASM/ .
dir=$(pwd)
file=$(basename "$2" .asm)
echo $dir

while getopts "c:e" opt; do
  case $opt in
    c) dosbox -c "mount C $dir" -c "C:" -c "startCom $file" ;;
    e) dosbox -c "mount C $dir" -c "C:" -c "startExe $file" ;;
    \?) echo "Unknown flag"; exit 1;;
  esac
done

rm -rf ./TASM
