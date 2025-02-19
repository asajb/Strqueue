	#include "strqueue.h"
	#include <iostream>
	#include <map>
	#include <vector>
	#include <string>
	#include <queue>
	#include <limits>
	#include <assert.h>
	#include <stddef.h>

	namespace {
		// Makra do logowania w trybie debugowania
	#define LOG_CALL_0_ARGS() \
		if constexpr (debug) { \
			mInitializer(); \
        	std::cerr << __func__ << "(" << ")\n"; \
    	}
	#define LOG_CALL_1_ARG(arg1) \
		if constexpr (debug) { \
			mInitializer(); \
			std::cerr << __func__ << "(" << (arg1) << ")\n"; \
		}
	#define LOG_CALL_2_ARGS(arg1, arg2) \
		if constexpr (debug) { \
			mInitializer(); \
			std::cerr << __func__ << "(" << (arg1) << ", " << (arg2) << ")\n"; \
		}
	#define LOG_CALL_3_ARGS(arg1, arg2, arg3) \
		if constexpr (debug) { \
			mInitializer(); \
			std::cerr << __func__ << "(" << (arg1) << ", " << (arg2) << ", \"" << (arg3) << "\")\n"; \
		}
	#define LOG_CALL_3_ARGS_NULL(arg1, arg2) \
		if constexpr (debug) { \
			mInitializer(); \
			std::cerr << __func__ << "(" << (arg1) << ", " << (arg2) << ", NULL)\n"; \
		}
	#define LOG_RETURN(val) \
		if constexpr (debug) { \
			std::cerr << __func__ << " returns " << val << "\n"; \
		}
	#define LOG_FAILED() \
		if constexpr (debug) { \
			std::cerr << __func__ << " failed\n"; \
		}
	#define LOG_QUEUE_DOES_NOT_EXIST(id) \
		if constexpr(debug) { \
			std::cerr << __func__ << ": queue " << id << " does not exist\n"; \
		}
	#define LOG_QUEUE_INDEX_OUT_OF_BOUNDS(id, position) \
		if constexpr (debug) { \
			std::cerr << __func__ << ": queue " << id << " does not contain string at position " << position << "\n"; \
		}
	#define LOG_DONE() \
		if constexpr (debug) { \
			std::cerr << __func__ << " done\n"; \
		}

		// Makro do włączania trybu debugowania
	#ifndef NDEBUG
		constexpr bool debug = true;
	#else
		constexpr bool debug = false;

	#endif

		// Zmienne globalne i funkcje pomocnicze
		
		// Pomocnicza funkcja zapewniająca bezpieczne inicjiwanie obiektów statycznych
		std::ios_base::Init& mInitializer(){
			static std::ios_base::Init mInitializer;
			return mInitializer;
		}

		// Mapa przechowywująca kolejki na podstawie unikalnych identyfikatorów
		std::map<unsigned long, std::vector<std::string>>& queue_map() {
			static std::map<unsigned long, std::vector<std::string>> que_mp;
			return que_mp;
		}

		// Licznik do generowania kolejnych identyfikatorów
		unsigned long& get_counter() {
			static unsigned long cnt = 0;
			return cnt;
		}

		std::string& get_last_string() {
			static std::string last_string;
			return last_string;
		}

		// Funkcja przydzielająca identyfikator nowej kolejce
		unsigned long give_id() {

			unsigned long ans;

			ans = get_counter();
			if constexpr (debug) {
				assert(ans < std::numeric_limits<unsigned long>::max());
			}
			get_counter()++;

			return ans;
		}
	}


	namespace cxx {

		unsigned long strqueue_new() {

			LOG_CALL_0_ARGS();
			
			unsigned long id = give_id();
			queue_map().insert({ id, {} }); // Inicjalizacja pustej kolejki

			LOG_RETURN(id);
			return id;
		}

		void strqueue_delete(unsigned long id) {

			LOG_CALL_1_ARG(id);

			if (!queue_map().erase(id)) {

				LOG_QUEUE_DOES_NOT_EXIST(id);
				return;

			}

			LOG_DONE();

		}

		size_t strqueue_size(unsigned long id) {

			LOG_CALL_1_ARG(id);

			auto it = queue_map().find(id);
			size_t answer;
			if (it != queue_map().end()) { // Jeśli istnieje kolejka o podanym id

				answer = it->second.size();

			}
			else {
				LOG_QUEUE_DOES_NOT_EXIST(id);
				answer = 0;
			}
			LOG_RETURN(answer);
			return answer;
		}

		void strqueue_insert_at(unsigned long id, size_t position, const char* str) {

			if (str == nullptr) {
				LOG_CALL_3_ARGS_NULL(id, position);
				LOG_FAILED();
				return;
			}

			LOG_CALL_3_ARGS(id, position, str);

			auto it = queue_map().find(id);
			if (it != queue_map().end()) { // Jeśli istnieje kolejka o podanym id

				if (position >= it->second.size()) {

					it->second.push_back(str); // Wstawiamy napis na końcu kolejki
				}

				else {

					it->second.insert(it->second.begin() + position, str); // Wstawiamy napis na pozycji position

				}

			}
			else {
				LOG_QUEUE_DOES_NOT_EXIST(id);
				return;
			}

			LOG_DONE();

		}

		void strqueue_remove_at(unsigned long id, size_t position) {

			LOG_CALL_2_ARGS(id, position);

			auto it = queue_map().find(id);
			if (it != queue_map().end()) { // Jeśli istnieje kolejka o podanym id

				if (position < it->second.size()) {

					it->second.erase(it->second.begin() + position); // Usuwamy napis na pozycji position

				}
				else {
					LOG_QUEUE_INDEX_OUT_OF_BOUNDS(id, position);
					return;
				}

			}
			else {
				LOG_QUEUE_DOES_NOT_EXIST(id);
				return;
			}

			LOG_DONE();

		}

		const char* strqueue_get_at(unsigned long id, size_t position) {

			LOG_CALL_2_ARGS(id, position);

			auto it = queue_map().find(id);
			if (it != queue_map().end()) { // Jeśli istnieje kolejka o podanym id

				if (position < it->second.size()) {

					get_last_string() = it->second[position];
					const char* ret = get_last_string().c_str();
					std::string retWithQuotes = "\"" + std::string(ret) + "\"";
					LOG_RETURN(retWithQuotes);
					return ret;

				}
				else {
					LOG_QUEUE_INDEX_OUT_OF_BOUNDS(id, position);
					std::string strNull= "NULL";
					LOG_RETURN(strNull);
					return nullptr;
				}

			}
			else {
				LOG_QUEUE_DOES_NOT_EXIST(id);
				std::string strNull = "NULL";
				LOG_RETURN(strNull);
				return nullptr;
			}

		}

		void strqueue_clear(unsigned long id) {

			LOG_CALL_1_ARG(id);

			auto it = queue_map().find(id);
			if (it != queue_map().end()) {

				it->second.clear();

			}
			else {
				LOG_QUEUE_DOES_NOT_EXIST(id);
				return;
			}

			LOG_DONE();
		}

		int strqueue_comp(unsigned long id1, unsigned long id2) {

			LOG_CALL_2_ARGS(id1, id2);

			auto it1 = queue_map().find(id1);
			auto it2 = queue_map().find(id2);

			if (it1 == queue_map().end()) LOG_QUEUE_DOES_NOT_EXIST(id1);
			if (it2 == queue_map().end()) LOG_QUEUE_DOES_NOT_EXIST(id2);

			// Ustawiamy wskaźniki na odpowiedni wektor lub pusty wektor, jeśli kolejka nie istnieje
			const std::vector<std::string> empty_vector;
			const auto& vec1 = (it1 != queue_map().end()) ? it1->second : empty_vector;
			const auto& vec2 = (it2 != queue_map().end()) ? it2->second : empty_vector;

			// Porównujemy po kolei elementy wektorów
			size_t min_size = std::min(vec1.size(), vec2.size());
			for (size_t i = 0; i < min_size; ++i) {
				if (vec1[i] < vec2[i]) {
					LOG_RETURN(-1);
					return -1;
				}
				if (vec1[i] > vec2[i]) {
					LOG_RETURN(1);
					return 1;
				}	
			}

			// Jeśli wszystkie porównane elementy są równe, porównujemy długości wektorów
			if (vec1.size() == vec2.size()) {
				LOG_RETURN(0);
				return 0;
			}
			if (vec1.size() < vec2.size()) {
				LOG_RETURN(-1);
				return -1;
			}
			else {
				LOG_RETURN(1);
				return 1;
			}

		}

	}