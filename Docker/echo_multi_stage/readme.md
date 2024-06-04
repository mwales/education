This project was a test of how to create a multi-stage container where I build
the application in a big container, but then the final container is a much
smaller container.

The alpine image with clang was over 400MB, but the echo_alpine container
just uses the base alpine without clang

To build the image:

```
docker build -t echo_alpine .
```

To see the image info / size:

```
docker image ls
REPOSITORY       TAG           IMAGE ID       CREATED         SIZE
echo_alpine      latest        90cd175c9ed8   5 minutes ago   7.81MB
echo_test        latest        73466a82f682   5 minutes ago   351MB
ubuntu           latest        bf3dc08bfed0   4 weeks ago     76.2MB
```

To run the container:

```
echo "Here Is Some Sample Text" | docker run --rm -i echo_alpine
echo service v0.1
hERE iS sOME sAMPLE tEXT
```

The -i option is for interactive (and is important for stdin working!)
The --rm option should remove the container when execution completes

