# pipex

리눅스의 파이프시스템을 간단하게 구현해보는 프로젝트이다.

## 사용방법

```bash
./pipex file1 cmd1 cmd2 cmd3 ... file2;
```
위와같이 실행하면

```bash
<file1 cmd1 | cmd2 | cmd 4 | ... >file2
```

이렇게 실행하는 것과 같은 결과가 나온다 예를 들어


```bash
./pipex infile "ls -l" "wc -l" outfile
```
 이렇게 실행한 값은
```bash
<infile ls -l | wc -l > outfile
```
이렇게 실행한 것과 같은 값을 출력한다.


또한
```bash
./pipex heredoc LIMITER cmd1 cmd2 ... file
``` 
이렇게 실행하면
```bash
<< LIMITER cmd1 | cmd2 | ... >> file
```
와 같은 값을 출력한다.
