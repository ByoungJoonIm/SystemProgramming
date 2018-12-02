## 개요
- 이 과정은 여러대의 서버를 구축하는 과정입니다.
- 실습할 여러대의 서버가 이미 있다면 이 과정을 건너 뛸 수 있습니다.
- 이 프로젝트에서는 공인IP를 사용하며 IP에 관련된 정보는 보안상의 이유로 업로드되지 않습니다.

## 여러대의 서버 구성
1. virtual box를 설치합니다. [Link](https://blog.naver.com/alice_k106/220967706683)의 과정 혹은 검색으로 설치가 가능합니다.
2. 새로운 instance를 생성한 뒤 리눅스를 설치합니다. [Link](https://blog.naver.com/qwe6168/221180446515)의 과정 혹은 검색으로 설치가 가능합니다.
3. 인스턴스를 복제합니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_01.jpg)</br>
  복제를 클릭합니다.</br></br>
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_02.jpg)</br>
  MAC 주소 초기화 체크박스를 체크합니다.</br></br>
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_03.jpg)</br>
  완전한 복제를 클릭합니다. 이 과정은 시간이 걸릴 수 있습니다.</br></br>
4. 3의 과정을 동일하게 수행하여 server1, server2, server3를 구성합니다.

## 호스트명 변경
호스트명 변경은 추후에 각각의 서버에서 동일한 명령어가 실행되지만, 다른 결과를 반환할 수 있도록 하는 과정입니다. 다른 명령어를 사용한다면 이 과정을 건너뛰어도 좋습니다.
1. 서버를 최초로 실행하면 다음과 같은 화면이 나올 수 있습니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_04.jpg)</br>
  기본 설정으로 ```Enter```를 누릅니다.</br></br>
2. 자신이 기존에 설정해 놓은 ID로 로그인합니다.
3. 터미널 창에 다음과 같이 입력합니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_05.jpg)</br>
  패스워드를 입력합니다.</br></br>
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_06.jpg)</br>
  위와 같이 수정한 뒤 :wq를 입력하고 ```Enter```를 누릅니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_07.jpg)</br>
  위의 과정과 동일하게 /etc/hosts 파일도 수정합니다.</br></br>
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_08.jpg)</br>
  빨간색 부분을 ```server2```로 수정합니다.</br></br>
4. 동일한 과정을 ```server1```, ```server3```에서 반복합니다. 설정은 재부팅 후 반영됩니다.
5. 재부팅 후 다음과 같이 확인할 수 있습니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_09.jpg)</br>

## IP 주소 확인
서버의 포트를 설정하기 이전에 가상머신과 공인 IP 주소를 확인해야 합니다.</br>
공인 IP는 [LINK](http://www.findip.kr/)에서 확인합니다. 가상 IP 주소는 다음과 같이 확인할 수 있습니다.
1. ```server```의 터미널에서 다음과 같이 입력합니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_10.jpg)</br>
  enp0s3의 inet이 가상머신의 IP 주소입니다. 일반적으로 `server1`,`server2`,`server3`모두 동일합니다.</br></br>
  
2. 1번이 에러가 나는 경우 다음과 같이 net-toos를 설치합니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_11.jpg)</br>


## 서버의 포트 설정
우리는 공용 IP를 사용하지만 각기 다른 서버를 구동할 것이므로 포트포워딩이 필요합니다. 
1. virtual box에서 ```server2``` 클릭 - 설정 - 네트워크 - 고급 - 포트포워딩의 순서로 클릭합니다.
2. 포트포워딩의 우측에 +를 클릭합니다.
3. 다음과 같이 입력합니다.
  ![Style Images](https://github.com/BJ-Lim/SystemProgramming/blob/master/captures/tutorial_01_install_12.jpg)</br>
  (1) 이름은 규칙의 이름입니다.</br>
  (2) 호스트IP는 공인 IP입니다.</br>
  (3) 호스트 포트는 호스트 PC에 접속할 때 사용되는 포트입니다.</br>
  (4) 게스트 포트는 가상머신에서 사용되는 포트입니다. 호스트 포트가 이 포트로 맵핑됩니다.</br>
4. 위 과정을 `server1`, `server3`에서도 동일하게 수행합니다.
