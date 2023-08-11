#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_BARS = 100;
const int BAR_WIDTH = WIDTH / NUM_BARS;

void drawBars(sf::RenderWindow& window, std::vector<int>& heights) {
    window.clear(sf::Color::Black);
    for (int i = 0; i < NUM_BARS; i++) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, -heights[i]));
        bar.setPosition(i * BAR_WIDTH, HEIGHT);
        bar.setFillColor(sf::Color::White);
        window.draw(bar);
    }
    window.display();
}

void bubbleSort(std::vector<int>& heights, sf::RenderWindow& window) {
    int n = heights.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (heights[j] > heights[j+1]) {
                std::swap(heights[j], heights[j+1]);
                drawBars(window, heights);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
}

void insertionSort(std::vector<int>& heights, sf::RenderWindow& window) {
    int n = heights.size();
    for (int i = 1; i < n; i++) {
        int key = heights[i];
        int j = i - 1;
        while (j >= 0 && heights[j] > key) {
            heights[j + 1] = heights[j];
            j = j - 1;
            drawBars(window, heights);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        heights[j + 1] = key;
    }
}

void heapify(std::vector<int>& heights, int n, int i, sf::RenderWindow& window) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heights[left] > heights[largest])
        largest = left;

    if (right < n && heights[right] > heights[largest])
        largest = right;

    if (largest != i) {
        std::swap(heights[i], heights[largest]);
        drawBars(window, heights);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        heapify(heights, n, largest, window);
    }
}

void heapSort(std::vector<int>& heights, sf::RenderWindow& window) {
    int n = heights.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(heights, n, i, window);

    for (int i = n - 1; i > 0; i--) {
        std::swap(heights[0], heights[i]);
        heapify(heights, i, 0, window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualizer");

    std::vector<int> heights(NUM_BARS);
    for (int i = 0; i < NUM_BARS; i++) {
        heights[i] = rand() % HEIGHT;
    }

    drawBars(window, heights);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Uncomment one of these to choose a sorting algorithm:
    //bubbleSort(heights, window);
    //insertionSort(heights, window);
    heapSort(heights, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}

