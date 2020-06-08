# CPPLINT
## Git 경로
* https://github.com/cpplint/cpplint.git
## Install cpplint
* apt install python-pip
* pip install cpplint
* cpplint --version
## Test
* cpplint example.cc
## Main options
* --linelength=80
* --filter=+whitespace/comments,-build/header_guard
  * +option: 해당 옵션 검사
  * -option: 해당 옵션 검사하지 않음
* --exclude_files=my_header.h, .*\.cc*
* --exclude=src/*.cc .*
* --headers=h,hpp
* --extensions=c,cc,h,c++,
## Use CPPLINT.cfg
* 미리 옵션을 설정해 놓고 사용할 수 있게 해줌
* Root까지 전역 탐색해가면서 모든 CPPLINT.cfg파일을 찾으려 함
* 기왕이면 cpplint를 사용할 최상위 경로에 하나 정의해 놓고 쓰면 될 듯
* 자세한 내용은 cpplint.py 찾아서 CPPLINT.cfg로 검색해보면 됨
### CPPLINT example
* vim ~/CPPLINT.cfg
  * set noparent #상위 .cfg를 더이상 찾지 않도록 해줌
  * filter=
  * linelength=
  * ...
