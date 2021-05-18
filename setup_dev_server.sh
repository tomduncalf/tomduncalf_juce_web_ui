# Only start the dev server in debug mode, and for the "Shared Code" target of the build
# (Xcode will try to run the script twice, once for the Shared Code and once for the actual build)
if [ "$CONFIGURATION" == "Debug" ] &&  [[ $TARGET_NAME == *" - Shared Code" ]]; then
  /usr/libexec/PlistBuddy -c "Set :DevServerIP `ipconfig getifaddr en0`" "${TARGET_BUILD_DIR}/../../Info-Standalone_Plugin.plist"
# echo  /usr/libexec/PlistBuddy -c "Set :DevServerIP `ipconfig getifaddr en0`" "${TARGET_BUILD_DIR}/../../Info-Standalone_Plugin.plist"

  if nc -w 5 -z localhost 3000 ; then
    if ! curl -s "http://localhost:3000/" ; then
      echo "Port already in use, server is either not running or not running correctly"
      exit 2
    fi
    else
      osascript <<END
tell application "Terminal"
do script "cd \"${SRCROOT}/../../ui\"; BROWSER=none yarn start"
end tell
END
  fi
fi
