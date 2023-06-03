#include <stdio.h>
#include <stdlib.h>

// 엘리베이터의 상태를 나타내는 열거형
typedef enum {
    IDLE,    // 대기 중
    MOVING,  // 이동 중
    SERVICING  // 서비스 중
} ElevatorStatus;

// 엘리베이터 구조체
typedef struct {
    int currentFloor;        // 현재 층
    int direction;           // 이동 방향 (-1: 아래로, 1: 위로)
    ElevatorStatus status;   // 엘리베이터 상태
    int queue[100];          // 대기 중인 요청을 저장하는 큐 (요청된 층 번호)
    int queueSize;           // 큐의 크기
} Elevator;

// 엘리베이터 동작 함수
void elevatorOperation(Elevator *elevator, int i) {
    switch (elevator->status) {
        case IDLE:
            if (elevator->queueSize > 0) {
                // 이동할 층이 있으면 이동 상태로 변경
                elevator->status = MOVING;
                printf("%d번 엘리베이터: %d 층 출발 \n", i+1, elevator->currentFloor);

            }
            break;
        case MOVING:
            // 엘리베이터 이동
            elevator->currentFloor += elevator->direction;
            printf("%d번 엘리베이터: %d 층 \n", i+1, elevator->currentFloor);

            // 현재 층에 도착한 경우 서비스 상태로 변경
            if (elevator->queueSize > 0 && elevator->currentFloor == elevator->queue[0]) {
                elevator->status = SERVICING;
            }
            break;
        case SERVICING:

            // 큐에서 처리된 요청 제거
            for (int i = 0; i < elevator->queueSize - 1; i++) {
                elevator->queue[i] = elevator->queue[i + 1];
            }
            elevator->queueSize--;

            // 서비스가 완료된 후에도 큐에 대기 중인 요청이 없으면 대기 상태로 변경
            if (elevator->queueSize == 0) {
                elevator->status = IDLE;
                printf("%d번 엘리베이터: %d 층 (서비스 완료) 운행 대기 \n", i+1, elevator->currentFloor);

            }
            else {
                // 현재 층의 요청 처리
                printf("%d번 엘리베이터: %d 층 (서비스 완료)\n", i+1, elevator->currentFloor);
                elevator->status = MOVING;
            }
            break;
    }
}

// SCAN 알고리즘 실행
void scanAlgorithm(Elevator *elevators, int numElevators) {
    // 여기서 각 elevator->queue를 정렬하고, direction을 골라줘야해
    for(int i=0; i<numElevators; i++){
        if(elevators[i].currentFloor > elevators[i].queue[0]) elevators[i].direction = -1;
        else elevators[i].direction = 1;
    }

    while (1) {
        // 모든 엘리베이터에 대해 동작 수행
        for (int i = 0; i < numElevators; i++) {
            elevatorOperation(&elevators[i], i);
        }
        printf("\n");

        // 모든 엘리베이터가 대기 상태인 경우 종료
        int allIdle = 1;
        for (int i = 0; i < numElevators; i++) {
            if (elevators[i].status != IDLE) {
                allIdle = 0;
                break;
            }
        }
        if (allIdle) {
            break;
        }
    }
}

int main() {
    // 엘리베이터 객체 생성
    Elevator elevators[3];
    int numElevators = sizeof(elevators) / sizeof(elevators[0]);

    // 엘리베이터 초기화
    // 각 엘리베이터는 0층에서 대기 중
    for (int i = 0; i < numElevators; i++) {
        elevators[i].currentFloor = 0;
        elevators[i].direction = 1;
        elevators[i].status = IDLE;
        elevators[i].queueSize = 0;
    }


    // 엘리베이터에 요청 도착 예시
    // 1번 엘리베이터에 2, 5층 요청 승객 탑승
    // 2번 엘리베이터에 3, 7층 요청 승객 탑승
    // 3번 엘리베이터에 1, 6층 요청 승객 탑승
    elevators[0].queue[elevators[0].queueSize++] = 2;
    elevators[0].queue[elevators[0].queueSize++] = 5;
    elevators[1].queue[elevators[1].queueSize++] = 3;
    elevators[1].queue[elevators[1].queueSize++] = 7;
    elevators[2].queue[elevators[2].queueSize++] = 1;
    elevators[2].queue[elevators[2].queueSize++] = 6;

    // SCAN 알고리즘 실행
    scanAlgorithm(elevators, numElevators);

    // 엘리베이터에 요청 도착 예시
    elevators[0].queue[elevators[0].queueSize++] = 2;
    elevators[1].queue[elevators[1].queueSize++] = 3;
    elevators[2].queue[elevators[2].queueSize++] = 1;

    // SCAN 알고리즘 실행
    scanAlgorithm(elevators, numElevators);

    return 0;
}
