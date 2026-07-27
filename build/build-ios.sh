#!/bin/sh
set -eu

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
repo_dir=$(dirname -- "$script_dir")
cd "$repo_dir"

ios_min_version=${IOS_MIN_VERSION:-17.4}
ios_sdk=${SDKROOT:-$(xcrun --sdk iphoneos --show-sdk-path)}
ios_cc=${CC:-$(xcrun -f clang)}
ios_ar=${AR:-$(xcrun -f ar)}
parallel_jobs=${JOBS:-$(sysctl -n hw.logicalcpu 2>/dev/null || echo 4)}

if ! command -v gmake >/dev/null 2>&1; then
  echo "error: GNU Make is required; install it with 'brew install make'" >&2
  exit 1
fi

./configure MODE=opt --enable-vfs --disable-fork --disable-backtrace
cp build/config-ios.h config.h

target_flags="-target arm64-apple-ios${ios_min_version} -isysroot ${ios_sdk}"

gmake -j"$parallel_jobs" \
  o/opt/blink/blink-embedded.a \
  CC="${ios_cc} ${target_flags}" \
  AR="$ios_ar"

"$ios_cc" $target_flags -iquote. \
  test/ios/embed-link-test.c \
  o/opt/blink/blink-embedded.a \
  -o o/opt/blink/blink-embed-link-test

file o/opt/blink/blink-embedded.a
file o/opt/blink/blink-embed-link-test
