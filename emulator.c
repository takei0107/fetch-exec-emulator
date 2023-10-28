#include"__data_path.h"
#include"__memory.h"
#include"__program_counter.h"
#include"__adder.h"

// 32bit汎用レジスタで表現できるサイズのMAX
#define MEMORY_SIZE_ALL (1L << 32)
// 命令メモリサイズ
#define MEMORY_SIZE_PGM   (MEMORY_SIZE_ALL/2)
// データメモリサイズ
#define MEMORY_SIZE_DATA  (MEMORY_SIZE_ALL - MEMORY_SIZE_PGM)

// 命令アドレス加算用のアダーの1回で進むアドレス
#define ADDER_STEP 4

static memory_all_t init_memory_all()
{
	memory_all_t memory_all;
	memory_all.pgm_area = memory_area_init(MEMORY_SIZE_PGM);
	memory_all.data_area = memory_area_init(MEMORY_SIZE_DATA);
	return memory_all;
}

static data_path_t init_data_path(memory_all_t memory_all, memory_addr_t pgm_start_addr)
{
	data_path_t data_path;

	// メモリ初期化
	data_path.memory_pgm = memory_all.pgm_area;
	data_path.memory_data = memory_all.data_area;

	// プログラムカウンタ初期化
	data_path.pgm_ctr = program_counter_init(pgm_start_addr);

	// adder初期化
	data_path.adder = adder_init(ADDER_STEP);

	return data_path;
}

int main()
{
	memory_all_t memory_all;
	data_path_t data_path;

	// 初期処理
	// 1. メモリ初期化
	// 2. 命令を命令メモリにロード
	// 3. 命令メモリの開始位置と終了位置を取得
	// 4. データパス作成
	memory_all = init_memory_all();

	// 疑似開始位置と終了位置
	uint32_t test_start = 0x00000000;
	uint32_t test_end = 0x00000010;

	data_path = init_data_path(memory_all, test_start);

	// クロック/ループ一回
	while(data_path.pgm_ctr.ptr < test_end) {

	}
}
