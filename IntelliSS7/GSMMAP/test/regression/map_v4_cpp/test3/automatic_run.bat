cp automatic_instructions.test %ITS_ROOT%/tools/src/gatorc/automatic_instructions.test
cp %ITS_ROOT%/tools/src/gatorc/generator .
cp %ITS_ROOT%/tools/src/gatorc/ossbuf1.test .
cp %ITS_ROOT%/tools/src/gatorc/ossbuf2.test .
awk -f %ITS_ROOT%/tools/src/gatorc/automatic_gatorc %ITS_ROOT%/tools/src/gatorc/automatic_instructions.test