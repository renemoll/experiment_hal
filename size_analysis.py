import re
import sys

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection


def process_file(filename):
    print('Processing file:', filename)
    with open(filename, 'rb') as f:
        analyse(f)

def analyse(stream):
    elffile = ELFFile(stream)
    
    # Just use the public methods of ELFFile to get what we need
    # Note that section names are strings.
    print('  %s sections' % elffile.num_sections())
    print()

    for s in elffile.iter_sections():
        try:
            print(f'  section: {s.name:<20} bytes: {s.data_size:<20} kb: {s.data_size/1024:<10.1f} type: {s["sh_type"]}')
        except TypeError:
            print(f'  section: {s.name}')

    flash = [".isr_vector", ".text", ".rodata", ".ARM", ".preinit_array", ".init_array", ".fini_array", ".data"]
    ram = [".data", ".bss", "._user_heap_stack"]

    flash_size = 0
    for name in flash:
        try:
            flash_size += elffile.get_section_by_name(name).data_size
        except AttributeError:
            pass

    ram_size = 0
    for name in ram:
        try:
            ram_size += elffile.get_section_by_name(name).data_size
        except AttributeError:
            pass

    print()
    print(f'  FLASH size: {flash_size} bytes')
    print(f'  RAM size:  {ram_size} bytes')
    print()

    symbol_table = elffile.get_section_by_name('.symtab')
    if not symbol_table:
        print('  No symbol table found. Perhaps this ELF has been stripped?')
        return

    # A section type is in its header, but the name was decoded and placed in
    # a public attribute.
    print('  Section name: %s, type: %s' %(symbol_table.name, symbol_table['sh_type']))

    # But there's more... If this section is a symbol table section (which is
    # the case in the sample ELF file that comes with the examples), we can
    # get some more information about it.
    if isinstance(symbol_table, SymbolTableSection):
        num_symbols = symbol_table.num_symbols()
        print(f"  Symbol table with {num_symbols} entries")
        print()

        table = []
        for i in range(num_symbols):
            symbol = symbol_table.get_symbol(i)
            if symbol.entry['st_size'] > 0:
                table.append({
                    'name': symbol.name,
                    'size': symbol.entry['st_size'],
                    'type': symbol.entry['st_info']['type'],
                    # 'entry': symbol.entry
                })

        functions = filter(lambda x: x['type'] == "STT_FUNC", table)
        functions_sorted = sorted(functions, key=lambda d: d['size'])
        functions_sorted.reverse()

        print(f"  Functions:")
        for el in functions_sorted:
            print(f"    symbol: {el['name']:<60} bytes: {el['size']:<10} kb: {el['size']/1024:<10.1f}")
        print()

        objects = filter(lambda x: x['type'] == "STT_OBJECT" or x['type'] == "STT_COMMON", table)
        objects_sorted = sorted(objects, key=lambda d: d['size'])
        objects_sorted.reverse()

        print(f"  Objects:")
        for el in objects_sorted:
            print(f"    symbol: {el['name']:<60} bytes: {el['size']:<10} kb: {el['size']/1024:<10.1f}")
        print()

        misc_symbols = filter(lambda x: x['type'] not in ["STT_OBJECT", "STT_COMMON", "STT_FUNC"], table)
        misc_symbols_sorted = sorted(misc_symbols, key=lambda d: d['size'])
        misc_symbols_sorted.reverse()

        print(f"  Misc objects:")
        for el in misc_symbols_sorted:
            print(f"    symbol: {el['name']:<50} bytes: {el['size']:<10} kb: {el['size']/1024:<10.1f}")
        print()

        print(f"  NOF non-zero symbols: {len(table)}")
        print(f"  NOF functions: {len(functions_sorted)}")
        print(f"  NOF objects: {len(objects_sorted)}")
        print(f"  NOF misc objects: {len(misc_symbols_sorted)}")
        print()

        # import pdb; pdb.set_trace()

        #
        # Todo: store the symbols in a bin for review
        #
        size_irq = 0
        size_gpio = 0
        size_app = 0
        size_hal = 0
        size_crt = 0

        symbols_app = ["main", "g_timer"]
        symbols_hal = [
            "SystemInit", 
            "SystemCoreClock",
            "AHBPrescTable",
            "uwTickPrio",
            "uwTick",
            "SystemCoreClock",
            "uwTickFreq",
        ]
        symbols_libc = [
            "__register_exitproc",
            "__retarget_lock_acquire_recursive", 
            "__retarget_lock_release_recursive", 
            "atexit", 
            "register_fini", 
            "__atexit0", 
            "__atexit", 
            "__atexit_recursive_mutex", 
            "__lock___atexit_recursive_mutex",
            "__udivmoddi4",
            "__aeabi_ldiv0",
            "__aeabi_idiv0",
        ]

        for el in list(functions_sorted):
            if re.match(".+_IRQHandler", el['name']) is not None or re.match(".+_Handler", el['name']) is not None:
                size_irq += el['size']
                functions_sorted.remove(el)
            elif re.match("LL_GPIO_.+", el['name']) is not None or re.match("HAL_GPIO_.+", el['name']) is not None:
                size_gpio += el['size']
                functions_sorted.remove(el)
            elif re.match("LL_.+", el['name']) is not None or re.match("HAL_.+", el['name']) is not None or el['name'] in symbols_hal:
                size_hal += el['size']
                functions_sorted.remove(el)
            elif re.match("__libc_.+.+", el['name']) is not None or el['name'] in symbols_libc:
                size_crt +=  el['size']
                functions_sorted.remove(el)
            elif el['name'] in symbols_app or "Timeout" in el['name']:
                size_app += el['size']
                functions_sorted.remove(el)

        for el in list(objects_sorted):
            if el['name'] in symbols_app:
                size_app += el['size']
                objects_sorted.remove(el)
            elif el['name'] in symbols_libc:
                size_crt +=  el['size']
                objects_sorted.remove(el)
            elif el['name'] in symbols_hal:
                size_hal += el['size']
                objects_sorted.remove(el)

        for el in list(misc_symbols_sorted):
            if re.match(".+_IRQHandler", el['name']) is not None or re.match(".+_Handler", el['name']) is not None:
                size_irq += el['size']
                misc_symbols_sorted.remove(el)

        print("  Symbol size per category")
        print(f"    IRQ related {size_irq:>20} bytes")
        print(f"    GPIO related {size_gpio:>20} bytes")
        print(f"    HAL related {size_hal:>20} bytes")
        print(f"    App related {size_app:>20} bytes")
        print(f"    CRT related {size_crt:>20} bytes")

        print("  Missed symbols:")
        print(f"    NOF functions: {len(functions_sorted)}")
        print(f"    NOF objects: {len(objects_sorted)}")
        print(f"    NOF misc objects: {len(misc_symbols_sorted)}")

        # import pdb; pdb.set_trace()

if __name__ == '__main__':
    for filename in sys.argv[1:]:
        process_file(filename)
