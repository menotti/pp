<a id="sec-top"></a>
# Tutorial oneAPI & DevCloud

Este tutorial contém informações básicas sobre como usar a oneAPI localmente e na DevCloud, bem como algumas dicas sobre ferramentas de compilação em geral. 

# Conteúdo
1. [Material](#sec-material)
2. [Acessando o DevCloud](#sec-acesso)
3. [Gerenciando os jobs](#sec-pbs)
4. [oneAPI](#sec-oneapi)
5. [FPGAs](#sec-fpga)

<a id="sec-material"></a>
# Material

Este material é baseado no que está disponível no repositório da Intel (https://github.com/intel/BaseKit-code-samples.git)

A edição foi feita usando Jupyter Notebooks (`oneAPI.ipynb`), a versão Markdown (`oneAPI.md`) é exportada a partir desta e seus links podem não funcionar corretamente. 

## Principais referências

* https://software.intel.com/en-us/oneapi
* https://devcloud.intel.com/oneapi/get-started/base-toolkit/
* https://spec.oneapi.com/oneAPI/
* https://github.com/intel/FPGA-Devcloud

[Voltar ao início](#sec-top)

<a id="sec-acesso"></a>
# Acessando o DevCloud 

A DevCloud pode ser acessada por SSH ou pelo navegados usando Jupyter Notebooks. 

[Neste link](https://devcloud.intel.com/oneapi/connect/) você pode criar uma conta e obter informações de acesso. 

[Voltar ao início](#sec-top)

<a id="sec-pbs"></a>
# Gerenciando os jobs com Portable Batch System (PBS)

Quando você acessa a DevCloud por SSH é direcionado para um nó de login que funciona como uma espécie de hall de entrada. A partir dele você pode solicitar acesso a outros nós do sistema. Geralmente isso é feito sem especificar exatamente qual nó você quer, mas as `properties` que ele tem. Além disso, você pode iniciar uma sessão interativa naquele nó ou submeter um trabalho (`job`) em modo `batch`, por meio do PBS.

## Obtendo informações do sistema

A seguir estão alguns comandos usados para obter informações do sistema:


```python
!echo "* Quantos servidores estão livres?"
!pbsnodes | grep "state = free" | wc -l
!echo
!echo "* Quantos servidores estão livres com FPGAs?"
!pbsnodes | grep -B 3 "fpga_runtime" | grep "state = free" | wc -l
!echo
!echo "* Qual o limite de tempo para os jobs na fila?"
!qmgr -c 'p q batch' | grep walltime
!echo
!echo "* Qual a configuração dos servidores disponíveis?"
!pbsnodes | grep properties | sort | uniq
!echo
!echo "* Quantas CPUs lógicas eu tenho para o Notebook?"
!taskset -c -p $$
!echo
!echo "* Quantos segundos faltam para terminar minha seção? Salve seu trabalho ANTES!"
!qstat -f $PBS_JOBID | grep Walltime.Remaining
!echo
!echo "* Saída completa do comando qstat para todos os jobs!"
!qstat -f 
```

    * Quantos servidores estão livres?
    35
    
    * Quantos servidores estão livres com FPGAs?
    5
    
    * Qual o limite de tempo para os jobs na fila?
    set queue batch resources_max.walltime = 24:00:00
    set queue batch resources_default.walltime = 06:00:00
    
    * Qual a configuração dos servidores disponíveis?
         properties = experimental,xeon,clx,ram192gb,net1gbe
         properties = fpga_compile,xeon,plat8153,skl,ram384gb,net1gbe
         properties = fpga_runtime,xeon,gold6128,skl,ram192gb,net1gbe,fpga,arria10
         properties = gen9,xeon,e-2176g,cfl,gpu,ram64gb,net1gbe,6cores,eus0024
         properties = jupyter,batch,xeon,gold6128,skl,ram192gb,net1gbe
    
    * Quantas CPUs lógicas eu tenho para o Notebook?
    pid 26628's current affinity list: 0-23
    
    * Quantos segundos faltam para terminar minha seção? Salve seu trabalho ANTES!
        Walltime.Remaining = 13448
    
    * Saída completa do comando qstat para todos os jobs!
    Job Id: 499602.v-qsvr-1.aidevcloud
        Job_Name = jupyterhub-singleuser
        Job_Owner = u34356@v-router.aidevcloud
        resources_used.cput = 00:00:19
        resources_used.energy_used = 0
        resources_used.mem = 216024kb
        resources_used.vmem = 2533676kb
        resources_used.walltime = 00:17:22
        job_state = R
        queue = jupyterhub
        server = v-qsvr-1.aidevcloud
        Checkpoint = u
        ctime = Mon Feb 17 05:05:48 2020
        Error_Path = v-hub:/dev/null
        exec_host = s001-n004/0
        Hold_Types = n
        Join_Path = n
        Keep_Files = n
        Mail_Points = n
        mtime = Mon Feb 17 05:05:49 2020
        Output_Path = v-hub:/dev/null
        Priority = 0
        qtime = Mon Feb 17 05:05:48 2020
        Rerunable = True
        Resource_List.nodect = 1
        Resource_List.nodes = 1:jupyter:ppn=1
        Resource_List.vmem = 94gb
        Resource_List.walltime = 04:02:00
        session_id = 22002
        Variable_List = PBS_O_QUEUE=jupyterhub,PBS_O_HOME=/,
    	PBS_O_PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin,
    	PBS_O_LANG=en_US.UTF-8,PBS_O_WORKDIR=/opt/jupyterhub,PBS_O_HOST=v-hub,
    	PBS_O_SERVER=c006,JPY_API_TOKEN=7593efb147194061ae94d0ce7615cd9a,
    	JUPYTERHUB_BASE_URL=/,JUPYTERHUB_CLIENT_ID=jupyterhub-user-u34356,
    	JUPYTERHUB_API_TOKEN=7593efb147194061ae94d0ce7615cd9a,
    	PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin,
    	PWD=/opt/jupyterhub,LANG=en_US.UTF-8,
    	JUPYTERHUB_API_URL=http://10.5.0.17:8081/hub/api,SHLVL=1,
    	JUPYTERHUB_USER=u34356,
    	JUPYTERHUB_OAUTH_CALLBACK_URL=/user/u34356/oauth_callback,
    	JUPYTERHUB_HOST=,JUPYTERHUB_SERVICE_PREFIX=/user/u34356/,
    	_=/usr/local/bin/qsub
        euser = u34356
        egroup = u34356
        queue_type = E
        etime = Mon Feb 17 05:05:48 2020
        submit_args = -P u34356
        start_time = Mon Feb 17 05:05:49 2020
        Walltime.Remaining = 13448
        start_count = 1
        fault_tolerant = False
        job_radix = 0
        proxy_user = u34356
        submit_host = v-hub
    


## Submetendo jobs

Para compilar e rodar os exemplos em modo batch é necessário criar scripts para serem submetidos no sistema. A seguir exemplos de scripts de compilação `build.sh` e execução `run.sh` usando um `Makefile` disponível no diretório corrente:

### Compilação
```bash
#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh
make clean
make all
```
### Execução
```bash
#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh
make run
```
### Submissão no PBS
O comando a seguir submete o script de compilação (`build.sh`) com uma lista de recursos (`-l resource_list`) usando o diretório corrente como prefixo (`-d .`). A lista de recursos especifia um único nó, com capacidade de compilação para FPGAs e 2 processadores:

`qsub -l nodes=1:fpga_compile:ppn=2 -d . build.sh`

Após a execução do job, são gerados arquivos de saída no seguinte padrão:
- <script_name>.eXXXX, para o stderr
- <script_name>.oXXXX, para o stdout

Onde XXXX corresponde ao job ID, impresso na tela após o comando qsub

### Monitorando 
O comando a seguir pode ser usado para acompanhar os jobs pendentes:

`watch -n 1 qstat -n -1`

Veja um exemplo de saída:

```code
Every 1.0s: qstat -n -1                                                                                                                             login-1: Fri Nov 22 12:26:23 2019


v-qsvr-1.aidevcloud:
                                                                                  Req'd       Req'd       Elap
Job ID                  Username    Queue    Jobname          SessID  NDS   TSK   Memory      Time    S   Time
----------------------- ----------- -------- ---------------- ------ ----- ------ --------- --------- - ---------
416823.v-qsvr-1.aidevc  u34356      jupyterh jupyterhub-singl   4253     1      1      94gb  04:02:00 R  00:19:43   s001-n045/0
416829.v-qsvr-1.aidevc  u34356      batch    STDIN             14313     1      2       --   06:00:00 R  00:01:13   s001-n140/0-1
416830.v-qsvr-1.aidevc  u34356      batch    STDIN              6093     1      2       --   06:00:00 R  00:00:39   s001-n083/0-1
```

### Modo interativo
Quando a DevCloud é acessada via SSH, entramos em um nó chamado servidor de login (headnode). Não é possível executar jobs neste nó, é preciso solicitar servidores específicos (computenode):
* Os seguintes nós pode rodar o Quartus, OpenCL e HLS: n130-n139.
* Os seguintes nós pode rodar OPAE com placas PAC: n137-n139.
* Há um total de 12 placas Arria 10 PAC Cards, 4 em cada um dos nós n137, n138 e n139.

Para consultar se nós livres estão disponíveis, execute o comando abaixo no servidor de login (headnode). A terminologia que usaremos é localnode (seu PC), headnode (nó de login) e computenode (servidores específicos). O computenode é uma máquina de alta potência para execução de compilações - um subconjunto deles possui placas PAC: n137, n138 e n139.

`pbsnodes -s v-qsvr-fpga | grep -B 4 fpga`

`pbsnodes -l free # lista todos os nós livres (apenas os nós 130-139 executam o x2go)`

Você obterá uma lista de nós livres e ocupados que se conectam às placas PAC.

Se houver um nó livre, ao executar o comando a seguir, você entrará em uma nova máquina dentro de um minuto ou mais. Se nenhuma máquina estiver disponível, você será colocado em uma fila.

Para efetuar login em uma máquina específica, execute um dos seguintes comandos:

`qsub -l nodes=s001-n130:ppn=2                  # (for s001-n130 through s001-n136)`

`qsub -q batch@v-qsvr-fpga -I -l nodes=s001-n137:ppn=2 # (for s001-n137 through s001-n139, and s001-n189)`

_Aparentemente estes comando não funcionam para as contas solitadas para o oneAPI, talvez seja para contas específicas para desenvolvedores FPGA._

Ao iniciar o comando qsub, você pode solicitar memória adicional com o seguinte comando. Nota: Cada trabalho ocupa 2 slots, portanto, quando você solicita 10G, na verdade é 10G * 2 = 20GB.

`-l h_vmem = 10G`

Agora você tem uma máquina de alta potência disponível para trabalhos de computação poderosos. Você só tem um console disponível, mas não há gráficos disponíveis. 

É possível solicitar uma seção interativa no prompt usando a opção `-I` em um nó com aceleradores FPGA:

`qsub -I -l nodes=1:fpga_runtime:ppn=2 -d .`

### Medindo o tempo de execução de um job
Inclua blocos com o comando `date` para medir o tempo de execução:


```python
#!/bin/bash
!echo
!echo start: $(date "+%y%m%d.%H%M%S.%3N")
!echo

# TODO list
!sleep 3

!echo
!echo stop:  $(date "+%y%m%d.%H%M%S.%3N")
!echo
```

    
    start: 191205.095134.553
    
    
    stop: 191205.095138.183
    


### Encadeando a execução de jobs
Para executar um job após a finalização de outro, é possível usar a sintaxe a seguinte:

```
qsub -l nodes=1:fpga_compile:ppn=2 -d . build_fpga_hw.sh
419431.v-qsvr-1.aidevcloud

qsub -l nodes=1:fpga_runtime:ppn=2 -d . run_fpga_hw.sh -W depend=afterok:419431.v-qsvr-1.aidevcloud

watch -n 1 qstat -n -1 

Every 1.0s: qstat -n -1                                                                                      login-1: Tue Nov 26 10:34:13 2019


v-qsvr-1.aidevcloud:
                                                                                  Req'd       Req'd       Elap
Job ID                  Username    Queue    Jobname          SessID  NDS   TSK   Memory      Time    S   Time
----------------------- ----------- -------- ---------------- ------ ----- ------ --------- --------- - ---------
419441.v-qsvr-1.aidevc  u34356      batch    build_fpga_hw.sh   1463     1      2       --   06:00:00 R  00:01:29   s001-n147/0-1
419443.v-qsvr-1.aidevc  u34356      batch    run_fpga_hw.sh      --      1      2       --   06:00:00 H       --     --
```

### Submetendo um comando shell 

Para submeter um comando _shell_ diretamente use um | (pipe)

```bash
echo lscpu | qsub -l nodes=1:fpga_compile:ppn=2
cat STDIN.* | grep  'Model name'
Model name:          Intel(R) Xeon(R) Platinum 8153 CPU @ 2.00GHz
rm STDIN.*
echo lscpu | qsub -l nodes=1:fpga_runtime:ppn=2
cat STDIN.* | grep  'Model name'
Model name:          Intel(R) Xeon(R) Gold 6128 CPU @ 3.40GHz
```
Isso é indica apenas para extrair informações dos nós e do sistema, pois scripts de compilação/execuçào são mais efetivos e não podem ser submetidos dessa forma. 

Note na saída acima que a configuração dos nós pode mudar de acordo com a funcionalidade solicitada. 

[Voltar ao início](#sec-top)

<a id="sec-sycl"></a>
# SYCL & DPC++ & oneAPI
O objetivo resumido desta API é oferecer uma interface de programação independente da plataforma. 

Uma plataforma oneAPI é composta por um _host_ e uma coleção de dispositivos. O _host_ normalmente é uma CPU com vários núcleos e os dispositivos são uma ou mais GPUs, FPGAs e outros aceleradores. O processador que serve como _host_ também pode ser o dispositivo escolhido para execução.

Cada dispositivo tem uma fila de comandos associada a ele. Um aplicativo que usa a oneAPI é executado no _host_, seguindo a semântica de execução C++ padrão. Para executar um objeto de função em um dispositivo, o aplicativo envia um grupo de comandos que contém o objeto de função para a fila do dispositivo. Um objeto de função contém uma definição de função junto com variáveis associadas. Um objeto de função enviado para uma fila também é chamado de _kernel paralelo de dados_ ou simplesmente um _kernel_.

O aplicativo em execução no _host_ e as funções em execução nos dispositivos se comunicam através da memória. A oneAPI define vários mecanismos para compartilhar memória na plataforma, dependendo dos recursos dos dispositivos:

| Mecanismo de compartilhamento de memória  | Descrição
| ---                                        | ---      
| Buffer objects                            | Um aplicativo pode criar objetos de buffer para passar dados para os dispositivos. Um buffer é um matriz de dados. Um grupo de comandos definirá objetos acessadores para identificar quais buffers são acessados nesta chamada para o dispositivo. O runtime oneAPI garantirá que o dados no buffer estão acessíveis para o função em execução no dispositivo. o mecanismo acessor de buffer está disponível em todas as plataformas oneAPI.
| Unified addressing                        | O endereçamento unificado garante que o host e todos os dispositivos compartilharão um espaço de endereço unificado. Os valores do ponteiro no espaço de endereço unificado vão se referir sempre ao mesmo local na memória.
| Unified shared memory                     | A memória compartilhada unificada permite que os dados sejam compartilhados através de ponteiros sem usar buffers e acessadores. Existem vários níveis de suporte para esse recurso, dependendo dos recursos do dispositivo subjacente.

Os grupos de comandos serão escalonados conforme o tipo de acesso à memória escolhido e a disponibilidade de recursos. 

## Conceitos fundamentais de C++

### Templates e C++ lambdas

Os lambdas C++, introduzidos pela primeira vez no C++11, são uma parte importante da maneira como o padrão SYCL é definido e implementado. O SYCL é necessário para lidar com tipos diferentes e transmitir funções, permitindo que objetos de função anônima sejam passados para os kernels SYCL. 

A biblioteca padrão C++ nos permite passar lambdas para funções, a fim de fornecer uma interface genérica para os algoritmos da biblioteca, para que os usuários possam definir o comportamento desejado. Nesse sentido, as lambdas nos permitem programar APIs de alto nível para uso genérico. 

Templates C++ e funções lambda são ferramentas realmente úteis para escrever aplicativos de alto nível. O SYCL, por outro lado, é uma interface que visa permitir que os desenvolvedores escrevam código limpo para acelerar a otimização de aplicativos de software em uma ampla gama de hardware. Para conseguir isso, o SYCL interage quase perfeitamente com os recursos modernos do C++, como código de templates e funções lambda, com o objetivo de facilitar o desenvolvimento de aplicativos complexos de alto nível e alto desempenho.

Se um lambda usa uma referência capturada por referência [&], está usando o objeto referido pela referência original, não a referência capturada:

```C++
#include <iostream>
 
auto make_function(int& x) {
  return [&]{ std::cout << x << '\n'; };
}
 
int main() {
  int i = 3;
  auto f = make_function(i); // the use of x in f binds directly to i
  i = 5;
  f(); // OK; prints 5
}
```

## Programação com API
Na programação com API são instanciados a fila do dispositivo e os buffers de memória, posteriormente é invocada uma função da API:
```C++
using namespace cl::sycl;

// declare host arrays
double *A = new double[M*N];
double *B = new double[N*P];
double *C = new double[M*P];

{
    // Initializing the devices queue with a gpu_selector
    queue q{gpu_selector()};

    // Creating 1D buffers for matrices which are bound to host arrays
    buffer<double, 1> a{A, range<1>{M*N}};
    buffer<double, 1> b{B, range<1>{N*P}};
    buffer<double, 1> c{C, range<1>{M*P}};

    mkl::transpose nT = mkl::transpose::nontrans;
    // Syntax
    //   void gemm(queue &exec_queue, transpose transa, transpose transb,
    //             int64_t m, int64_t n, int64_t k, T alpha,
    //             buffer<T,1> &a, int64_t lda,
    //             buffer<T,1> &b, int64_t ldb, T beta,
    //             buffer<T,1> &c, int64_t ldc);
    // call gemm
    mkl::blas::gemm(q, nT, nT, M, P, N, 1.0, a, M, b, N, 0.0, c, M);
}
// when we exit the block, the buffer destructor will write result back to C.
```

## Programação direta
Na programação direta também são instanciados a fila do dispositivo e os buffers de memória, definidos com entrada e/ou saída. Então é criada uma lambda C++ e passada como parâmetro do `parallel_for`. 

```C++
using namespace cl::sycl;

// declare host arrays
double *Ahost = new double[M*N];
double *Bhost = new double[N*P];
double *Chost = new double[M*P];

{
    // Initializing the devices queue with a gpu_selector
    queue q{gpu_selector()};

    // Creating 2D buffers for matrices which are bound to host arrays
    buffer<double, 2> a{Ahost, range<2>{M,N}};
    buffer<double, 2> b{Bhost, range<2>{N,P}};
    buffer<double, 2> c{Chost, range<2>{M,P}};

    // Submitting command group to queue to compute matrix c=a*b
    q.submit([&](handler &h){
        // Read from a and b, write to c
        auto A = a.get_access<access::mode::read>(h);
        auto B = b.get_access<access::mode::read>(h);
        auto C = c.get_access<access::mode::write>(h);

        int WidthA = a.get_range()[1];

        // Executing kernel
        h.parallel_for<class MatrixMult>(range<2>{M, P}, [=](id<2> index){
            int row = index[0];
            int col = index[1];

            // Compute the result of one element in c
            double sum = 0.0;
            for (int i = 0; i < WidthA; i++) {
                sum += A[row][i] * B[i][col];
        }
            C[index] = sum;
        });
    });
}
// when we exit the block, the buffer destructor will write result back to C.
```

## Compilação para FPGAs

A compilação para FPGA é bastante demorada por causa da etapa de síntese do hardware. A seguir estão algumas dicas para adiar a síntese (emulação) e evitar que ela se repita sem necessidade (device link). 

### Modelo SYCL 

No modelo SYCL um host é conectado a dispositivos OpenCL. Seletores são usados para escolher os dipositivos. Emuladores e hardware real de FPGA podem ser explicitamente escolhidos. O seletor padrão escolherá o dispositivo com melhor desempenho, por exemplo, usar um acelerador se ele encontrar um no sistema. 

```C++
    // FPGA device selector:  Emulator or Hardware
    #ifdef FPGA_EMULATOR
        intel::fpga_emulator_selector device_selector;
    #elif defined(FPGA)
        intel::fpga_selector device_selector;
	#else
        // Initializing the devices queue with the default selector
        // The device queue is used to enqueue the kernels and encapsulates
        // all the states needed for execution  
        default_selector device_selector;       
	#endif
	
    std::unique_ptr<queue> device_queue;

    // Catch device selector runtime error 
    try {
        device_queue.reset( new queue(device_selector) );
    } catch (cl::sycl::exception const& e) {
        std::cout << "Caught a synchronous SYCL exception:" << std::endl << e.what() << std::endl;
        std::cout << "If you are targeting an FPGA hardware, please "
                    "ensure that your system is plugged to an FPGA board that is set up correctly"
                    "and compile with -DFPGA" << std::endl;
        std::cout << "If you are targeting the FPGA emulator, compile with -DFPGA_EMULATOR." << std::endl;
        return ;
    }
       
    std::cout << "Device: "
            << device_queue->get_device().get_info<info::device::name>()
            << std::endl;
```

### Exemplo: Compilando para Emulação

Compile o projeto usando o seguinte comando:

`dpcpp -fintelfpga src/compile_flow.cpp -o a.fpga_emu -DFPGA_EMULATOR`

Execute o seguinte comando para verificar a exatidão do programa:

`./a.fpga_emu`

### Fluxo de geração de RTL e Relatório de Otimização

Uma compilação de FPGA possui dois estágios: 1. Geração de RTL, que leva minutos. 2. Síntese do software Intel® Quartus Prime, que pode levar horas.

O relatório de otimização é gerado após a conclusão do primeiro estágio. Para gerar RTL e o relatório de otimização, execute o seguinte comando:

`dpcpp -fintelfpga -fsycl-link src/compile_flow.cpp -o dev_early.a -Xshardware`

Um relatório de otimização baseado em HTML é gerado no diretório `dev_early.prj/reports/report.html`.

O relatório de otimização contém informações relacionadas ao desempenho sobre o projeto, como as seguintes:

- Informação de loops
- Utilização estimada de recursos
- Configuração de memória
- Informações sobre cluster e pipelining

Este relatório é um ponto de parada inicial para você melhorar iterativamente seu projeto sem esperar horas para que a síntese seja concluída.

### Fluxo de geração de hardware

Execute as seguintes etapas:

Certifique-se de que o seletor de dispositivo correto seja escolhido usando o cabeçalho do utilitário FPGA:
`#include <CL/sycl/intel/fpga_extensions.hpp>`

`fpga_hardware_device device_selector;`

Gere hardware a partir do arquivo de origem ou do arquivo de imagem produzido quando você gerou RTL e o relatório de otimização:

- Para gerar hardware diretamente do arquivo de origem, execute o seguinte comando:

`dpcpp -fintelfpga src/compile_flow.cpp -o a.out -Xshardware` 

Esse comando também gera um relatório de otimização ao concluir o primeiro estágio da compilação do FPGA.

- Para gerar hardware a partir do objeto de imagem gerado por um fluxo de geração RTL, execute o seguinte comando:

`dpcpp -fintelfpga dev_early.a -o a.out -Xshardware`

### Device link

Para evitar que o acelerador seja sintetizado sem necessidade, é possível separar o seu código do código do host em arquivos diferentes.

#### Examplo

Considere o exemplo a seguir, onde um programa é separado em dois arquivos, `main.cpp` e `kernel.cpp`. Somente o arquivo `kernel.cpp` contém o código do dispositivo.

No processo normal de compilação, a geração da imagem do dispositivo FPGA ocorre durante o tempo do link. Isso indica que qualquer alteração no arquivo `main.cpp` ou `kernel.cpp` irá gerar novamente uma imagem de dispositivo FPGA.

```
# normal compile command
dpcpp -fintelfpga main.cpp kernel.cpp -Xshardware -o link.fpga
```

A figura a seguir mostra esse processo de compilação:

![Compilação Normal](figs/normal_compile.png)


Se você deseja iterar no código do host e evitar um longo tempo de compilação para o seu dispositivo FPGA, considere usar um link de dispositivo para separar a compilação do dispositivo e do host:

```
# device link command
dpcpp -fintelfpga -fsycl-link=image <input files> [options]
```

A compilação se dará em 3 passos:

1. Compile a parte do dispositivo (horas) usando o comando: 

   ```
   dpcpp -fintelfpga -fsycl-link=image kernel.cpp -o dev_image.a -Xshardware
   ```
   Para programas genéricos, os arquivos de entrada devem incluir todos os arquivos de origem que contêm o código do dispositivo.


2. Compile a parte do host (segundos) usando o comando:
   
   ``` 
   dpcpp -fintelfpga main.cpp -c host.o
   ```
   Para programas genéricos, os arquivos de entrada devem incluir todos os arquivos de origem que contêm apenas código do host.

3. Crie o device link (segundos) usando o comando:

   ```
   dpcpp -fintelfpga host.o dev_image.a -o device_link.fpga
   ```
   Para um programa genérico, a entrada deve ter N (N>=0) arquivos de objeto host e um arquivo de imagem do dispositivo.

** NOTA: ** Você só precisa executar as etapas 2 e 3 ao modificar arquivos somente para host.

A figura a seguir mostra o processo de compilação do link do dispositivo:

![Compilação com Device link](figs/device_link.png)


## oneAPI Data Parallel C++ (DPC++)
DPC++ é a linguagem da oneAPI. Ela fornece os recursos necessários para definir funções paralelas de dados e iniciá-las nos dispositivos. O idioma é composto pelos seguintes componentes:
- *C++:* Todo programa DPC++ também é um programa C++ e deve oferecer suporte ao C++ 11 ou posterior. 
- *SYCL:* O DPC++ inclui a linguagem SYCL. O SYCL permite a definição de funções paralelas de dados que podem ser transferidas para dispositivos e define APIs e classes de tempo de execução que são usadas para orquestrar as funções transferidas. Uma implementação compatível com DPC++ também deve ser uma implementação compatível com SYCL 1.2.1 (ou posterior).
- *Extensões de linguagem DPC++:* Uma implementação compatível com DPC++ deve oferecer suporte aos recursos de idioma especificados. Isso inclui memória compartilhada unificada (USM), filas ordenadas e reduções. Algumas extensões são necessárias apenas quando a implementação do DPC++ oferece suporte a uma classe específica de dispositivo, conforme resumido na tabela de extensões:

| Extension | CPU | GPU | FPGA | Test
| ---     | --- | --- | ---  | ---
| USM | Required | Required | Required | usm
| In-order queues | Required | Required | Required | NA
| Optional lambda name | Required | Required | Required | NA 
| Reduction | Required | Required | Required | NA 
| Subgroups | Required | Required | Not required | sub_group
| Data flow pipes | Not required | Not required | Required | fpga_tests

Um breve resumo das extensões é o seguinte:
- Memória compartilhada unificada (USM) - define acessos à memória baseados em ponteiro e interfaces de gerenciamento. Oferece a capacidade de criar alocações visíveis e com valores consistentes de ponteiro no host e no dispositivo. Diferentes níveis de capacidade do USM são definidos, correspondendo a diferentes níveis de dispositivo e suporte à implementação.
- Filas em ordem - define semânticas simples em ordem para filas, para simplificar padrões comuns de codificação. Adiciona a classe `ordered_queue`.
- Nome lambda opcional - remove o requisito de nomear manualmente lambdas que definem kernels. Simplifica a codificação e permite a composição com bibliotecas. Ainda é possível nomear lambdas manualmente, se desejado, como na depuração.
- Redução - fornece abstração de redução para a forma ND-range do parallel_for. Melhora a produtividade, fornecendo o padrão de redução comum sem codificação explícita e permite a existência de implementações otimizadas para combinações de dispositivo, tempo de execução e propriedades de redução.
- Subgrupos - define um agrupamento de itens de trabalho em um grupo de trabalho. A sincronização de itens de trabalho em um subgrupo pode ocorrer independentemente dos itens de trabalho em outros subgrupos, e os subgrupos expõem operações de comunicação entre os itens de trabalho do grupo. Os subgrupos geralmente mapeiam para o hardware SIMD quando ele existe.
- Data flow pipes - permite uma comunicação eficiente filas (FIFO) no DPC++, um mecanismo comumente usado na descrição de algoritmos para arquiteturas espaciais, como FPGAs.

[Voltar ao início](#sec-top)

<a id="sec-fpga"></a>
# FPGAs

## Tutoriais

### Compilação

O ciclo de desenvolvimento mais comumente usado para FPGAs segue os três passoas a seguir:
- Emulation: compilação e execução no emulador em CPU para verificar se o programa está funcionalmente correto.
- RTL report: geração de relatórios antes da síntese para detectar possíveis gargalos.
- Hardware: Geração do hardware para FPGA e ligação com o programa host.

O exemplo fornecido tem os seguintes definições:

```
    #if defined(FPGA_EMULATOR)
    intel::fpga_emulator_selector device_selector;
    #elif defined(CPU_HOST)
    host_selector device_selector;
    #else
    intel::fpga_selector device_selector;
    #endif
```
    
De acordo com os parâmetros de compilação, o código será adptado para execução no emulador, cpu ou FPGA respectivamente. 

### Compilando para emulação

Compile o projeto usando o seguinte comando:

`dpcpp -fintelfpga src/compile_flow.cpp -o a.fpga_emu -DFPGA_EMULATOR`

Rode com o seguinte comando para verificar se o programa está correto:

`./a.fpga_emu`

### Geração de RTL e relatório de otimização

A compilação para FPGAs possui dois passos:
- Geração de RTL, a qual leva minutos;
- Síntese no Quartus, a qual pode levar horas. 

Ambas usam o seletor de dispositivos `intel::fpga_selector device_selector;`

O relatório de otimização é gerado no primeiro passo com o seguinte comando:

`dpcpp -fintelfpga -fsycl-link src/compile_flow.cpp -o dev_early.a -Xshardware`

O relatório será gerado em `dev_early.prj/reports/report.html` e possui informações de desempenho, entre elas:
- Informação de loops 
- Estivativa de recursos usados 
- Configuração de memória
- Informação de clustering e pipelining 

Este relatório é um passo prévio para melhorar o projeto sem ter que esperar horas pela síntese. 

### Geração do Hardware 

A geração de hardware pode ser feita de duas formas:

1. Diretamente a partir do código fonte com o comando:

`dpcpp -fintelfpga src/compile_flow.cpp -o a.out -Xshardware`

Este comando também gera um relatório de otimização quando completa o primeiro estágio. 

2. A partir do objeto gerado no fluxo anterior (RTL) com o comando:

`dpcpp -fintelfpga dev_early.a -o a.out -Xshardware`

### Compilação separada para o host e o device

Em certas ocasiões, pode ser útil compilar apenas o código do host sem a necessidade de alterar o código do acelerador que contem o bitstream e pode demorar horas para ser gerado. 

Na compilação combinada, o bitstream é gerado durante a ligação, com o comando:

`dpcpp -fintelfpga main.cpp kernel.cpp -Xshardware -o link.fpga`

Para separar as etapas, possibilitando recompilar apenas o código do host, pode ser fazer o seguinte:

1. Fazer a compilação do kernel (horas):

`dpcpp -fintelfpga -fsycl-link=image kernel.cpp -o dev_image.a -Xshardware`

2. Fazer a compilação do host (segundos):

`dpcpp -fintelfpga main.cpp -c -o host.o`

3. Fazer a ligação dos arquivos (segundos):

`dpcpp -fintelfpga host.o dev_image.a -o device_link.fpga`

[Voltar ao início](#sec-top)
