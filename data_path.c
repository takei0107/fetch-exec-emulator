#include"data_path.h"

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

data_path_t init_data_path(data_path_init_params params)
{
	data_path_t data_path;
	memory_all_t memory_all;
	
	// レジスタユニット初期化
	data_path.register_unit = init_register_unit();

	// メモリ初期化
	memory_all = init_memory_all();
	data_path.memory_pgm = memory_all.pgm_area;
	data_path.memory_data = memory_all.data_area;

	// プログラムカウンタ初期化
	data_path.pgm_ctr = program_counter_init(params.pgm_start_addr, params.pgm_end_addr);
	// adder初期化
	data_path.adder = adder_init(ADDER_STEP);

	return data_path;
}

int data_path_exec(data_path_t data_path)
{
	memory_addr_t pgm_ctr_ptr, pgm_end_addr;
	ins_raw_t ins_raw;
	ins_decoded_t decoded;

	pgm_end_addr = data_path.pgm_ctr.pgm_end_addr;
	// クロック/ループ一回
	while((pgm_ctr_ptr = data_path.pgm_ctr.ptr) < pgm_end_addr) {
		data_path.pgm_ctr.ptr = adder_perform(data_path.adder, pgm_ctr_ptr);
		ins_raw = fetch_ins(data_path.memory_pgm, pgm_ctr_ptr);
		decoded = decode(ins_raw);
	}
	return 0;
}
