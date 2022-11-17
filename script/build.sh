set -e # stop when having issues
# set -x # debug

# ------------------------------------------------------------------------------
# Config: move to config.sh
# ------------------------------------------------------------------------------

SRC_PATH=/home/pxhoang/pxhoang/git/proxy
IMG_PATH=/home/pxhoang/pxhoang/git/proxy.img

# ------------------------------------------------------------------------------
# Prototype
# ------------------------------------------------------------------------------

function cmd_build() {
  echo -e "cmd_build"
  pushd $SRC_PATH >/dev/null
  cmake --preset=x64-debug
  cmake --build --preset=x64-debug
  popd >/dev/null
}

function cmd_run() {
  echo -e "cmd_run"
  pushd $IMG_PATH/build/x64-debug/bin/stream >/dev/null
  ./stream
  popd >/dev/null
}

function cmd_clean() {
  echo -e "cmd_clean"
  rm -rf $IMG_PATH
}

# ------------------------------------------------------------------------------
# Interface
# ------------------------------------------------------------------------------

cmd=$1
case $cmd in
'build')
  cmd_build
  ;;
'clean')
  cmd_clean
  ;;
'run')
  cmd_run
  ;;
*)
  echo default
  ;;
esac
