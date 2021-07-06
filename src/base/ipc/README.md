# Linux IPC 테스트
## 참조링크
* https://doitnow-man.tistory.com/110
## 종류
* Pipe
* Named Pipe
* Message Queue
* Shared Memory
* Memory Map
* Socket
## 각 IPC 특징
| 종류 | Pipe | Named Pipe | Message Queue | Shared Memory | Memory Map | Socket |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 용도 | 부모-자식 | 다른 프로세스 | 멀티 프로세스 | 다른 프로세스 | 다른 프로세스 | 다른 시스템 간 |
| 공유매개 | 파일 | 파일 | 메모리 | 메모리 | 파일+메모리 | 소켓 |
| 통신 단위 | Stream | Stream| 구조체 | 구조체 | 페이지 | Stream |
| 통신 방향 | 단방향 | 단방향 | 단방향 | 양방향 | 양방향 | 양방향 |
| 통신 범위 | 동일 시스템 | 동일 시스템 | 동일 시스템 | 동일 시스템 | 동일 시스템 | 동일 + 외부 시스템 |
## IPC 설명
* 각 폴더 README.md 참조
## 빌드 및 테스트 설명
* 각 폴더 README.md 참조

