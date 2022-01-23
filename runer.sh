#!/usr/bin/bash
# Run App

APP="wallet_alert"
ARGS=$*

cmake-build-debug/$APP "$ARGS"

exit 0