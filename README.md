# cs50x

Personal solutions to Harvard's Computer Science 50x course: https://www.edx.org/course/introduction-computer-science-harvardx-cs50x

## running in docker

some files can't be compiled as they are on macos. it's easy to fix with running ubuntu in docker:

setup: `docker run -it --name myubuntuindocker -v /path-to-your-code:/cs ubuntu`
run it once it was shut down: `docker start myubuntuindocker -i`
