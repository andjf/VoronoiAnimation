MAKEFLAGS += silent

default:
	gcc -std=c17 -Wall -Wextra -o ./produce ./src/*.c -lm

optimized:
	gcc -std=c17 -Wall -Wextra -O3 -o ./produce ./src/*.c -lm

debug:
	gcc -std=c17 -Wall -Wextra -ggdb3 -o ./produce ./src/*.c -lm

go:
	gcc -std=c17 -Wall -Wextra -o ./producetemp ./src/*.c -lm; ./producetemp; rm ./producetemp

animation:
	mkdir -p frames; make optimized; ./produce; rm -f ./produce; ffmpeg -y -r 30 -f image2 -s 800x800 -i frames/frame%03d.png -vcodec libx264 -crf 15 -pix_fmt yuv420p animation.mp4; rm -rf frames
