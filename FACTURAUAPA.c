#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct producto
{
  char productoId[10];
  char productoNombre[20];
  char productoDescripcion[30];
  int cantidad;
  float precioPorUnidad;
  float impuesto;
  float subTotal;
};

struct factura
{
  char cliente[50];
  char fecha[50];
  char facturaNumero[50];
  char telefono[30];
  int cantidadDeProductos;
  float totalImpuesto;
  float totalNeto;
  struct producto productos[50];
};

void headerFactura(char nombre[50], char fecha[30], char telefono[30], char numeroFactura[30])
{
  printf("\n \n ");
  printf("\\t \t \t \t \tt \t \t \t  \t UAPA Tecnologia");
  printf("\n \t \t \t \t \t \t \t Calle 5-W Esq. 2W, Urbanización Lucerna, Código postal No. 11516");
  printf("\n \t \t \t \t \t \t \t \t   Santo Domingo Este, República Dominicana");
  printf("\n \t \t \t \t  \t \t \t \t    Tel: (809) 483-0100 Fax: (809) 483-4313");
  printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\nFecha   : %s \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t No. Factura    : %s", fecha, numeroFactura);
  printf("\nCliente : %s \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Teléfono       : %s", nombre, telefono);
  printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  printf("%-10s%-20s%-20s%-30s%-20s%-20s%-20s%-20s\n", "No.", "Id Producto", "Producto", "Descripcion", "Cantidad", "Precio", "Impuesto", "Sub Total");
  printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n");
};

void detalleFactura(int numeroArticulo, struct producto producto)
{
  printf("%-10d%-20s%-20s%-30s%-20d%-20f%-20f%-20f\n", numeroArticulo, producto.productoId, producto.productoNombre, producto.productoDescripcion, producto.cantidad, producto.precioPorUnidad, producto.impuesto, producto.subTotal);
}

void facturaFinal(struct factura factura)
{
  printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  printf("%150s", "Total Articulos:");
  printf("%*d\n", 10, factura.cantidadDeProductos);

  printf("%150s", "Total Impuestos:");
  printf("%*f\n", 10, factura.totalImpuesto);

  printf("%150s", "Total General:");
  printf("%*f\n", 10, factura.totalNeto);
  
}

int main()
{
  int opcion, cantidad;
  char guardarFactura = 's';
  char bandera = 's';
  char nombre[50];

  while (bandera == 's')
  {
    struct factura factura;
    struct factura listaFacturas;

    int opcion, i;
    float articulo, total;
    float impuestoArticulo = 0.0068;
    float totalImpuesto = 0;
    float totalGeneral = 0;
    float totalCantidad = 0;

    printf("===========================================UAPA TECNOLOGIA==============================================");
    printf("\n1. Generar Nueva Factura");
    printf("\n2. Salir");

    printf("\n\nEscoja una opción para continuar: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
      case 1:
        printf("%-25s : ", "Nombre del cliente");
        fgetc(stdin);
        fgets(factura.cliente, 50, stdin);
        factura.cliente[strlen(factura.cliente) - 1] = 0;
        strcpy(factura.fecha, __DATE__);

        printf("%-25s : ", "Cantidad de productos");
        scanf("%d", &cantidad);

        for (int i = 0; i < cantidad; i++)
        {
          fgetc(stdin);
          printf("\n\n");

          printf("Datos del Producto No. %d: \n", i + 1);

          printf("%-25s : ", "Id del producto");
          fgets(factura.productos[i].productoId, 10, stdin);
          factura.productos[i].productoId[strlen(factura.productos[i].productoId) - 1] = '\0';

          printf("%-25s : ", "Nombre del producto");
          fgets(factura.productos[i].productoNombre, 20, stdin);
          factura.productos[i].productoNombre[strlen(factura.productos[i].productoNombre) - 1] = '\0';

          printf("%-25s  : ", "Descripción del producto");
          fgets(factura.productos[i].productoDescripcion, 30, stdin);
          factura.productos[i].productoDescripcion[strlen(factura.productos[i].productoDescripcion) - 1] = '\0';

          printf("%-25s : ", "Cantidad del Producto");
          scanf("%d", &factura.productos[i].cantidad);

          printf("%-25s : ", "Precio por unidad");
          scanf("%f", &factura.productos[i].precioPorUnidad);
          
          float precioArticulo = (factura.productos[i].cantidad * factura.productos[i].precioPorUnidad);
          float impuesto = precioArticulo * impuestoArticulo;

          factura.productos[i].impuesto = impuesto;
          factura.productos[i].subTotal = precioArticulo + impuesto;

          totalCantidad += factura.productos[i].cantidad;
          totalImpuesto += impuesto;
          totalGeneral += factura.productos[i].subTotal;
        }

        factura.cantidadDeProductos = totalCantidad;
        factura.totalImpuesto = totalImpuesto;
        factura.totalNeto = totalGeneral;

        headerFactura(factura.cliente, factura.fecha, factura.telefono, factura.facturaNumero);

        for (int i = 0; i < cantidad; i++)
        {
          detalleFactura(i, factura.productos[i]);
        }

        facturaFinal(factura);
        break;
      case 2:
        printf("\nGracias por utilizar nuestro proyecto");
        exit(0);
        break;
      default:
        printf("\nLa opción especificada no esta disponible\n\n");
        break;
    }

    printf("\nDigite la letra s si desea seguir facturando: ");
    scanf("%s", &bandera);
  }

  printf("\n\n");
  return 0;
}