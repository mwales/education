This project was me trying to test how stdin and stdout worked for a
containerized application.

To build the image:

```
docker build -t echo_test .
```

To see the image info / size:

```
docker image ls
REPOSITORY       TAG           IMAGE ID       CREATED         SIZE
echo_test        latest        73466a82f682   5 minutes ago   351MB
ubuntu           latest        bf3dc08bfed0   4 weeks ago     76.2MB
```

To run the container:

```
echo "Here Is Some Sample Text" | docker run --rm -i echo_test
echo service v0.1
hERE iS sOME sAMPLE tEXT
```

The -i option is for interactive (and is important for stdin working!)
The --rm option should remove the container when execution completes

